// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemy.h"

#include "EnemyAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyEnemy::AMyEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComp"));
	this->GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	EnemyLaughTime = 5;

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
	EnemyStateEnum = EEnemyState::IDLE;

	GetWorldTimerManager().SetTimer(LaughTimerHandle,this,&AMyEnemy::EnemyLaugh,1.0f,true);
	
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

void AMyEnemy::EnemyLaugh()
{
	EnemyLaughTime--;
	if(EnemyLaughTime<0 )
	{
		UGameplayStatics::PlaySoundAtLocation(this,LaughSound,GetActorLocation());
		EnemyLaughTime = 5;
	}
}

void AMyEnemy::Dead()
{
	EnemyStateEnum = EEnemyState::Dead;
	this->Controller->Destroy();
	this->GetMesh()->SetSimulatePhysics(true);
	this->GetCharacterMovement()->DisableMovement();
	//this->GetCharacterMovement()->DisableMovement();
	
}

