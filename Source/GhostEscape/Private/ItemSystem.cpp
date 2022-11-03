// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSystem.h"

// Sets default values for this component's properties
UItemSystem::UItemSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	Pistol = false;
	Rifle = false;

	PistolAmmo = 0;
	// ...
}


//여기서 사용자의 저장된 정보를 불러올 예정
// Called when the game starts
void UItemSystem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UItemSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

