// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostEscape/Public/MyCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
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
	this->GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	this->SetHidden(false);
	bDead = false;
	
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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

//라인트레이스를 사방으로 쏴서 맞는 적에게 공포 데미지를 준다.
//플레이어 액터를 기준으로 좌측과 우측에 선을 긋는다.
//두 선의 x,y축 사이에 적이 있으면 공격 성공 z축은 플레이어의 키높이 +- 오차만큼 
//공격 소리 포함 (비명지르기, 소리는 여러개의 소리를 같이 쓸거다.)
void AMyCharacter::Attack()
{
	UE_LOG(LogTemp,Log,TEXT("Attack"));
	FHitResult Hit;

	
	FVector Start = FPS_Camera->GetComponentLocation();
	FVector End =  Start + (FPS_Camera->GetForwardVector()) * 1500.0f;
	FVector Left = End;
	Left.X -= 500.0;
	FVector Right = End;
	Right.X += 500.0;
	
	
	FCollisionQueryParams QueryParams;
	ECollisionChannel Channel = ECollisionChannel::ECC_Visibility; //어떤 객체가 다른 객체의 시야를 차단하는지를 판단하기 위해 트레이스 채널 사용
	QueryParams.AddIgnoredActor(this); //이 라인 트레이스를 실행하는 액터를 무시한다.

	
	
	GetWorld()->LineTraceSingleByChannel(Hit,Start,End,Channel,QueryParams);
		
	GetWorld()->LineTraceSingleByChannel(Hit,Start,Left,Channel,QueryParams);
	GetWorld()->LineTraceSingleByChannel(Hit,Start,Right,Channel,QueryParams);

	DrawDebugLine(GetWorld(),Start,End,FColor::Red,false, 2.0f);
	DrawDebugLine(GetWorld(),Start,Left,FColor::Blue,false, 2.0f);
	DrawDebugLine(GetWorld(),Start,Right,FColor::Green,false, 2.0f);


	UGameplayStatics::PlaySoundAtLocation(GetWorld(),AttackSound,GetActorLocation());


	
}
void AMyCharacter::Run()
{
	this->GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}
void AMyCharacter::StopRun()
{
	this->GetCharacterMovement()->MaxWalkSpeed = 300.0f;
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




