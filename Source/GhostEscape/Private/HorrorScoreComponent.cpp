// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorScoreComponent.h"

#include "InGameUI.h"

// Sets default values for this component's properties
UHorrorScoreComponent::UHorrorScoreComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHorrorScoreComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHorrorScoreComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHorrorScoreComponent::getHorrorScore(int amount)
{
	
	HorrorScore+=amount;
	IngameUI->UpdateHorrorScoreTxt(HorrorScore);
	UE_LOG(LogTemp,Log,TEXT("Got Score : %d"),HorrorScore);
}


