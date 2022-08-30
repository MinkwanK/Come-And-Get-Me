// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostEscape/Public/MyCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyEnemy.h"
#include "MyPlayerController.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	AIPerceptionStimuliSourceComp = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AIPerceptionStumuliSourceComponent"));
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetRelativeLocation(FVector(30.0f,0.0f,BaseEyeHeight));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300;
	CameraBoom->bUsePawnControlRotation = true;
	FPS_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPS_Camera"));
	FPS_Camera->SetupAttachment(CameraBoom);
	AIPerceptionStimuliSourceComp->RegisterForSense(Sight);
	this->GetCharacterMovement()->MaxWalkSpeed = 300.0;
	this->SetHidden(false);
	
	bDead = false;
	Invisible = true;
	State = 0;
	InvisibleTime = 5;
	GameOverScaryWidgetTimer = 3;
	
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	FString levelname = UGameplayStatics::GetCurrentLevelName(this);
	
	if(levelname == FString("StartMap"))
	{
		UE_LOG(LogTemp,Log,TEXT("StartMap"));
		AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController());
		PlayerController->ShowMainMenuWidget();
	}
	else
	{
		AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController());
		PlayerController->HideMainMenuWidget();
	}
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



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

	}
}

void AMyCharacter::MoveForward(float Value)
{
	if(Controller != nullptr && Value != 0.0f)
	{
		const FRotator YawRotation(0,Controller->GetControlRotation().Yaw,0); //카메라가 바라보는 방향을 기준으로 캐릭터가 이동하기 위해서 yaw값을 구한다.
		const FVector Direction = UKismetMathLibrary::GetForwardVector(YawRotation); //YawRotation을 가리키는 벡터를 구한다.
		AddMovementInput(Direction,Value);
		
	}
}

/*
 <투명상태일때 가능한 플레이어의 민간인 공격>
기본적으로 투명상태인데 공격 버튼을 누르면 투명 상태가 풀리며 소리를 지른다. 그리고 플레이어의 상태는 공격 상태가 된다.
사람의 시야각안에 공격모드로 된 플레이어가 들어오면 큰 공포 데미지를 입는다.
공격 소리 포함 (비명지르기, 소리는 여러개의 소리를 같이 쓸거다.)
*/
void AMyCharacter::Attack()
{
	if(Invisible==true)
	{
		UE_LOG(LogTemp,Log,TEXT("Attack"));
	
		Invisible = false;
		State = 1;
		UGameplayStatics::PlaySoundAtLocation(GetWorld(),AttackSound,GetActorLocation());

		GetWorldTimerManager().SetTimer(InvisibleTimerHandle,this,&AMyCharacter::InvisibleTimeLoss,1.0f,true);
	}
	
}

void AMyCharacter::InvisibleTimeLoss()
{
	InvisibleTime--;
	if(InvisibleTime<0)
	{
		Invisible = true;
		InvisibleTime = 5;
		GetWorldTimerManager().ClearTimer(InvisibleTimerHandle);
	}
}

void AMyCharacter::Run()
{
	this->GetCharacterMovement()->MaxWalkSpeed = 600.0;
}
void AMyCharacter::StopRun()
{
	this->GetCharacterMovement()->MaxWalkSpeed = 300.0;
}
void AMyCharacter::ActiveCrouch()
{
	if(bIsCrouched)
	{
		UnCrouch();
	}
	else
		Crouch();
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






