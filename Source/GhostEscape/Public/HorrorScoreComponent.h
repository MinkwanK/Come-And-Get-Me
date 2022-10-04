// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HorrorScoreComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GHOSTESCAPE_API UHorrorScoreComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY()
	class UInGameUI* IngameUI;
public:	
	// Sets default values for this component's properties
	UHorrorScoreComponent();

	void getHorrorScore(int amount);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UInGameUI> BP_InGameUI;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly,Category=HorrorScore)
	int HorrorScore = 0;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
