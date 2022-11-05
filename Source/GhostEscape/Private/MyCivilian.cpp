// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCivilian.h"


#include "NPCExitTargetPoint.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyCivilian::AMyCivilian()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	
	this->GetCharacterMovement()->MaxWalkSpeed = 200.0f;

	CanSeePlayer = false;
	CanHear = false;
	state[0] = true;
	state[1] = false;
	state[2] = false;
	ScaredSoundCnt = 2;
}


// Called when the game starts or when spawned
void AMyCivilian::BeginPlay()
{
	Super::BeginPlay();

	
	GetWorldTimerManager().SetTimer(ScaredSoundTimerHandle,this,&AMyCivilian::SoundCntLoss,1.0f,true);
	
	
	
}

void AMyCivilian::SoundCntLoss()
{
	
	ScaredSoundCnt--;
	
	if(ScaredSoundCnt<0)
	{
		ScaredSoundCnt = 2.0;
		if(state[1]==true)
		UGameplayStatics::PlaySoundAtLocation(GetWorld(),ScaredSound,this->GetActorLocation());
		GetWorldTimerManager().ClearTimer(ScaredSoundTimerHandle);
	}
}


void AMyCivilian::GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	OutLocation = GetMesh()->GetSocketLocation("Eye");
	OutRotation = GetMesh()->GetSocketRotation("Eye");
}

// Called every frame
void AMyCivilian::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	
}

// Called to bind functionality to input
void AMyCivilian::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

