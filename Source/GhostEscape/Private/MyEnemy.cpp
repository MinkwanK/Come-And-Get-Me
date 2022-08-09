// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemy.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyEnemy::AMyEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->GetCharacterMovement()->MaxWalkSpeed = 300.0f;

}

//액터의 eye 뷰 포인트를 반환한다. 이 함수를 쓰면 weapn 및 ai는 이 뷰포인트를 사용할 것이다.
void AMyEnemy::GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	OutLocation = GetMesh()->GetSocketLocation("Eye");
	OutRotation = GetMesh()->GetSocketRotation("Eye");
}


// Called when the game starts or when spawned
void AMyEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

