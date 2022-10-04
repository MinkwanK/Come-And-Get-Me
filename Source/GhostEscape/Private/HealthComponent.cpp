// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "GameFramework/CharacterMovementComponent.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::LoseHealth(int amount,AMyCivilian* Civilian)
{
	
	Health-=amount;
	UE_LOG(LogTemp,Log,TEXT("%d"),Health);
	
	if(Health<=0)
	{
		UE_LOG(LogTemp,Log,TEXT("Dead"));
		Civilian->GetController()->Destroy();
		Civilian->GetCharacterMovement()->DisableMovement();
		Civilian->GetMesh()->SetSimulatePhysics(true);
		Health = 0;
	}
}

