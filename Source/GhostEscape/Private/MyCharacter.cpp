// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostEscape/Public/MyCharacter.h"

#include "ItemWidget.h"
#include "MyCivilian.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyEnemy.h"
#include "MyPlayerController.h"
#include "ToolBuilderUtil.h"
#include "../../../Plugins/Developer/RiderLink/Source/RD/thirdparty/spdlog/include/spdlog/details/tcp_client-windows.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
AMyCharacter::AMyCharacter()
{

	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;


	
	AIPerceptionStimuliSourceComp = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AIPerceptionStumuliSourceComponent"));
	

	bCanSeeCivilian = false;
	
	


	//총기 메쉬 숨기기
		


	
	FPS_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPS_Camera"));
	FPS_Camera->SetupAttachment(GetMesh(),TEXT("head"));
	FPS_Camera->bUsePawnControlRotation = true;

	PlayerLightComp = CreateDefaultSubobject<USpotLightComponent>(TEXT("PlayerLightComponent"));
	PlayerLightComp->SetupAttachment(FPS_Camera);
	PlayerLightComp->SetIntensity(0.0f);

	NoiseEmitterComp = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("NoiseEmitterComponent"));
	
	AIPerceptionStimuliSourceComp->RegisterForSense(Sight);
	AIPerceptionStimuliSourceComp->RegisterForSense(Hearing);

	ItemSystemComp = CreateDefaultSubobject<UItemSystem>(TEXT("ItemSystemComp"));
	
	
	this->GetCharacterMovement()->MaxWalkSpeed = 300.0;
	this->SetHidden(false);

	PlayerStateEnum = EPlayerState::IDLE;
	DetectedObject = nullptr;
	
	bDead = false;
	bLight = false;
	bShowItemWidget = false;
	bCanAim = false;

	EndTimer = 5;
	GameOverScaryWidgetTimer = 3;
	MaxMovementNoiseRange = 100.0f; //Max Noise Range when Walking
	

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	FString levelname = UGameplayStatics::GetCurrentLevelName(this);
	AMyPlayerController* MyPlayerController =  Cast<AMyPlayerController>(this->Controller);
	if(levelname == "StartMap")
	{
		
		MyPlayerController->ShowMainMenuWidget();
	}
	else if(levelname == "TestMap" || levelname == "Stage1")
	{
		MyPlayerController->ShowCrossHair();
	}

	this->GetMesh()->GetChildComponent(1)->SetHiddenInGame(true);
	/*
	FString meshname = this->GetMesh()->GetChildComponent(1)->GetName();
	UE_LOG(LogTemp,Log,TEXT("찾고자 하는 Mesh는 %s 입니다!!!"),*meshname);
	*/
    if(levelname == "Stage1")
    {
	    UGameplayStatics::GetAllActorsWithTag(GetWorld(),"Pistol",Weaponary);
    	UGameplayStatics::GetAllActorsWithTag(GetWorld(),"Enemy",EnemyAry);
    	Weaponary[0]->SetActorHiddenInGame(true);
    	Weaponary[0]->SetActorEnableCollision(false);
    	EnemyAry[0]->SetActorHiddenInGame(true);
    	EnemyAry[0]->SetActorEnableCollision(false);
    }

	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//라인트레이스 결과 저장 변수
	FHitResult Hit; 

	//라인트레이스 시작 벡터 변수
	FVector Start = FPS_Camera->GetComponentLocation();
	//라인트레이스 도착 벡터 변수
	FVector End = Start +FPS_Camera->GetForwardVector()*300.0f;


	ECollisionChannel Channel = ECollisionChannel::ECC_Visibility;
	FCollisionQueryParams QueryParams;
	//Player를 라인트레이스 충돌에서 제외
	QueryParams.AddIgnoredActor(this);
	
	//라인트레이스 발사
	GetWorld()->LineTraceSingleByChannel(Hit,Start,End,Channel,QueryParams);
	//라인트레이스 발사 선 표시
	//DrawDebugLine(GetWorld(),Start,End,FColor::Green);

	if(Hit.GetActor() != nullptr)
	{
		//라인 트레이스에 맞은 Actor의 Tag가 Item 이라면
		if(Hit.GetActor()->ActorHasTag("Item"))
		{
			AMyPlayerController* MyPlayerController =  Cast<AMyPlayerController>(this->Controller);

			//아이템 위젯이 보여지지 않고 있는 상태여야 한다.
			if(MyPlayerController && bShowItemWidget != true)
			{
				//아이템 위젯 활성화
				MyPlayerController->ShowItemWidget(Hit.GetActor());
				bShowItemWidget = true;
				DetectedObject = Hit.GetActor();
			}
		}
	}
	else
	{
		AMyPlayerController* MyPlayerController =  Cast<AMyPlayerController>(this->Controller);
		
		if(MyPlayerController && bShowItemWidget == true)
		{
			//UE_LOG(LogTemp,Log,TEXT("HideItemWidget"));
			MyPlayerController->HideItemWidget();
			bShowItemWidget = false;
			DetectedObject = nullptr;
		}
	}


		
	
	

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&AMyCharacter::Jump);
	PlayerInputComponent->BindAction("Jump",IE_Released,this,&AMyCharacter::StopJumping);
	PlayerInputComponent->BindAction("Run",IE_Pressed,this,&AMyCharacter::Run);
	PlayerInputComponent->BindAction("Run",IE_Released,this,&AMyCharacter::StopRun);
	PlayerInputComponent->BindAction("Crouch",IE_Pressed,this,&AMyCharacter::ActiveCrouch);
	PlayerInputComponent->BindAction("Crouch",IE_Released,this,&AMyCharacter::ActiveCrouch);
	PlayerInputComponent->BindAction("Attack",IE_Pressed,this,&AMyCharacter::Attack);
	PlayerInputComponent->BindAction("Light",IE_Pressed,this,&AMyCharacter::LightOn);
	PlayerInputComponent->BindAction("Interact",IE_Pressed,this,&AMyCharacter::Interact);
	PlayerInputComponent->BindAction("Aim",IE_Pressed,this,&AMyCharacter::Aim);
	PlayerInputComponent->BindAction("Aim",IE_Released,this,&AMyCharacter::NotAim);


	PlayerInputComponent->BindAxis("Move Right",this,&AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Move Forward",this,&AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Turn",this,&AMyCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up",this,&AMyCharacter::AddControllerPitchInput);


}
void AMyCharacter::MoveRight(float Value)
{
	if(Controller != nullptr && Value != 0.0f)
	{
		const FRotator YawRotation(0,Controller->GetControlRotation().Yaw,0); //카메라가 바라보는 방향을 기준으로 캐릭터가 이동하기 위해서 yaw값을 구한다.
		const FVector Direction = UKismetMathLibrary::GetRightVector(YawRotation); //YawRotation을 가리키는 벡터를 구한다.
		AddMovementInput(Direction,Value);

		MakeNoise(1,this,GetActorLocation(),MaxMovementNoiseRange,"Noise");


	}
}

void AMyCharacter::MoveForward(float Value)
{
	if(Controller != nullptr && Value != 0.0f)
	{
		const FRotator YawRotation(0,Controller->GetControlRotation().Yaw,0); //카메라가 바라보는 방향을 기준으로 캐릭터가 이동하기 위해서 yaw값을 구한다.
		const FVector Direction = UKismetMathLibrary::GetForwardVector(YawRotation); //YawRotation을 가리키는 벡터를 구한다.
		AddMovementInput(Direction,Value);

		MakeNoise(1,this,GetActorLocation(),MaxMovementNoiseRange,"Noise");



		
	}
}

void AMyCharacter::Aim()
{
	//Player의 상태가 조준 상태라면
	PlayerStateEnum = EPlayerState::AIM;

	//Player가 Pistol을 장착한 상태라면
	if(ItemSystemComp->Pistol == true)
	{
		bCanAim = true;
		UGameplayStatics::PlaySoundAtLocation(GetWorld(),PistolRaiseSound,GetActorLocation());
		this->GetMesh()->GetChildComponent(1)->SetHiddenInGame(false);
	}
}

void AMyCharacter::NotAim()
{
	PlayerStateEnum = EPlayerState::IDLE;
	this->GetMesh()->GetChildComponent(1)->SetHiddenInGame(true);
	bCanAim = false;
}



//라인트레이스 쓰기
//캐릭터가 태어난 후부터 계속 해서 쏘고, 민간인이 맞으면 UI 띄우기

void AMyCharacter::Attack()
{
		if(PlayerStateEnum == EPlayerState::AIM)
		{
			//라인트레이스 결과 저장 변수
			FHitResult Hit; 

			//라인트레이스 시작 벡터 변수
			FVector Start = FPS_Camera->GetComponentLocation();
			//라인트레이스 도착 벡터 변수
			FVector End = Start +FPS_Camera->GetForwardVector()*1500.0f;


			ECollisionChannel Channel = ECollisionChannel::ECC_Visibility;
			FCollisionQueryParams QueryParams;
			//Player를 라인트레이스 충돌에서 제외
			QueryParams.AddIgnoredActor(this);
	
			//라인트레이스 발사
			GetWorld()->LineTraceSingleByChannel(Hit,Start,End,Channel,QueryParams);
			//라인트레이스 발사 선 표시
			//DrawDebugLine(GetWorld(),Start,End,FColor::Red,false,3);

			UGameplayStatics::PlaySoundAtLocation(GetWorld(),AttackSound,GetActorLocation());

			if(Hit.GetActor() != nullptr)
			{
				UE_LOG(LogTemp,Log,TEXT("Hit!"));
				if(Hit.GetActor()->ActorHasTag("Enemy"))
				{
					AMyEnemy* Enemy = Cast<AMyEnemy>(Hit.GetActor());
					Enemy->HealthComp->LoseHealth(50);

					if(Enemy->HealthComp->HP <= 0 && Enemy->EnemyStateEnum != EEnemyState::Dead)
					{
			
						Enemy->Dead();

						//GetWorldTimerManager().SetTimer(EndTimerHandle,this,&AMyCharacter::EndTimeLoss,1.0f);
						
					}
				}
			}
		}
}



void AMyCharacter::Interact()
{
	if(DetectedObject != nullptr) //감지한 오브젝트가 있다면
	{
		if(DetectedObject->ActorHasTag("Pistol"))
		{
			UE_LOG(LogTemp,Log,TEXT("This is Pistol"));
			ItemSystemComp->Pistol = true;
			DetectedObject->Destroy();
			DetectedObject = nullptr;

			this->GetMesh()->GetChildComponent(1)->SetHiddenInGame(true);
			PlayAnimMontage(Equip_Pistol_Montage);
			this->GetMesh()->GetChildComponent(1)->SetHiddenInGame(false);

			UGameplayStatics::PlaySoundAtLocation(GetWorld(),ScarySound,GetActorLocation());
			EnemyAry[0]->SetActorHiddenInGame(false);
			EnemyAry[0]->SetActorEnableCollision(true);
		}

		else if(DetectedObject->ActorHasTag("Book")) //나중에 개선!!
		{
			UE_LOG(LogTemp,Log,TEXT("This is Book"));
			ItemSystemComp->BookStack = true;
			UGameplayStatics::PlaySoundAtLocation(GetWorld(),PickBookStack,GetActorLocation());
			DetectedObject->Destroy();
			DetectedObject = nullptr;

			
			TArray<AActor*> AllActors;

			UGameplayStatics::GetAllActorsWithTag(GetWorld(),"Brian",AllActors);

			AMyCivilian* Civilian = Cast<AMyCivilian>(AllActors[0]);
			UGameplayStatics::PlaySoundAtLocation(GetWorld(),AttackSound,Civilian->GetActorLocation());
			Civilian->Controller->Destroy();
			Civilian->GetMesh()->SetSimulatePhysics(true);
			Weaponary[0]->SetActorHiddenInGame(false);
			Weaponary[0]->SetActorEnableCollision(true);

			

			
			
		}
	}
}




		//UGameplayStatics::PlaySoundAtLocation(GetWorld(),AttackSound,GetActorLocation());
		//MakeNoise(1,this,GetActorLocation(),1000.0f,"AttackNoise");
		/*
			if(GetDistanceTo(TargetCivilian) <= 500)
			{
				UE_LOG(LogTemp,Log,TEXT("공격 가능!"));
			}
		*/			
		
	
	
	





void AMyCharacter::Run() //Change Movement Speed and NoiseRange
{ 
	if(bCanAim != true) //조준하고 있는 상태에선 달릴 수 없다.
	{
		this->GetCharacterMovement()->MaxWalkSpeed = 600.0;
		MaxMovementNoiseRange = 500.0f;
	}
}
void AMyCharacter::StopRun()
{
	this->GetCharacterMovement()->MaxWalkSpeed = 300.0;
	MaxMovementNoiseRange = 100.0f;
}
void AMyCharacter::ActiveCrouch()
{
	if(bIsCrouched)
	{
		UE_LOG(LogTemp,Log,TEXT("UnCrouch"));
		UnCrouch();
		MaxMovementNoiseRange = 100.0f;
	}
	else
	{
		UE_LOG(LogTemp,Log,TEXT("Crouch"));
		Crouch();
		MaxMovementNoiseRange = 5.0f;
	}
}

void AMyCharacter::LightOn()
{
	

	if(bLight)
	{
		UE_LOG(LogTemp,Log,TEXT("Light Off"));
		PlayerLightComp->SetIntensity(0.0f);
		bLight = false;
	}
	else
	{
		UE_LOG(LogTemp,Log,TEXT("Light ON"));
		PlayerLightComp->SetIntensity(1000.0f);
		bLight = true;
	}

}




void AMyCharacter::PlayerDead()
{
	if(bDead==true)
	{

		AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController());

		if(PlayerController != nullptr)
		{
			PlayerController->ShowScaryGameOverWidget();
			GetWorldTimerManager().SetTimer(GameOverScaryWidget_TimerHandle,this,&AMyCharacter::GameOverScaryWidget_TimeLoss,1.0f,true);
		
		}
	}
}

void AMyCharacter::GameOverScaryWidget_TimeLoss()
{
	UE_LOG(LogTemp,Log,TEXT("Gameover scary Timer"))
	GameOverScaryWidgetTimer--;
	if(GameOverScaryWidgetTimer<0)
	{
		AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController());
		if(PlayerController != nullptr)
		{
			GetWorldTimerManager().ClearTimer(GameOverScaryWidget_TimerHandle);
			PlayerController->HideScaryGameOverWidget();
			PlayerController->ShowRestartWidget();
		}
	}
}
/*
void AMyCharacter::EndTimeLoss()
{
	EndTimer--;
	if(EndTimer<0)
	{
		AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController());
		if(PlayerController!=nullptr)
		{
			GetWorldTimerManager().ClearTimer(EndTimerHandle);
			PlayerController->ShowScaryGameOverWidget();
			PlayerController->ShowMainMenuWidget();
		}
	}
	
}
*/
void AMyCharacter::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	AMyEnemy* Enemy = Cast<AMyEnemy>(Other);
	
	if(Enemy)
	{
		bDead = true;
		Enemy->Destroy();
		PlayerDead();
	}
}






