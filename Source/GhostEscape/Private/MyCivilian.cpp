// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCivilian.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyCivilian::AMyCivilian()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}


// Called when the game starts or when spawned
void AMyCivilian::BeginPlay()
{
	Super::BeginPlay();
	
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

