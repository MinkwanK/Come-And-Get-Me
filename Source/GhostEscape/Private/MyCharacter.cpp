// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostEscape/Public/MyCharacter.h"

#include "ItemWidget.h"
#include "MyCivilian.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyEnemy.h"
#include "MyPlayerController.h"
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
	
	
	
	
	


	
	FPS_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPS_Camera"));
	FPS_Camera->SetupAttachment(GetMesh(),TEXT("head"));
	FPS_Camera->bUsePawnControlRotation = true;

	PlayerLightComp = CreateDefaultSubobject<USpotLightComponent>(TEXT("PlayerLightComponent"));
	PlayerLightComp->SetupAttachment(FPS_Camera);
	PlayerLightComp->SetIntensity(0.0f);

	NoiseEmitterComp = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("NoiseEmitterComponent"));
	
	AIPerceptionStimuliSourceComp->RegisterForSense(Sight);
	AIPerceptionStimuliSourceComp->RegisterForSense(Hearing);


	
	
	this->GetCharacterMovement()->MaxWalkSpeed = 300.0;
	this->SetHidden(false);
	
	bDead = false;
	bLight = false;
	State = 0;
	bShowItemWidget = false;
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
	else if(levelname == "TestMap")
	{
		MyPlayerController->ShowCrossHair();
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
	FVector End = Start +FPS_Camera->GetForwardVector()*125.0f;


	ECollisionChannel Channel = ECollisionChannel::ECC_Visibility;
	FCollisionQueryParams QueryParams;
	//Player를 라인트레이스 충돌에서 제외
	QueryParams.AddIgnoredActor(this);
	
	//라인트레이스 발사
	GetWorld()->LineTraceSingleByChannel(Hit,Start,End,Channel,QueryParams);
	//라인트레이스 발사 선 표시
	DrawDebugLine(GetWorld(),Start,End,FColor::Green);

	if(Hit.GetActor() != nullptr)
	{
		if(Hit.GetActor()->ActorHasTag("Weapon"))
		{
			AMyPlayerController* MyPlayerController =  Cast<AMyPlayerController>(this->Controller);
			
			if(MyPlayerController && bShowItemWidget != true)
			{
			
				MyPlayerController->ShowItemWidget(Hit.GetActor());
				bShowItemWidget = true;
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




//라인트레이스 쓰기
//캐릭터가 태어난 후부터 계속 해서 쏘고, 민간인이 맞으면 UI 띄우기

void AMyCharacter::Attack()
{
		State = 1;
	
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
		DrawDebugLine(GetWorld(),Start,End,FColor::Red,false,3);
}

void AMyCharacter::Interact()
{
	
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
	this->GetCharacterMovement()->MaxWalkSpeed = 600.0;
	MaxMovementNoiseRange = 500.0f;
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
		PlayerLightComp->SetIntensity(500.0f);
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






