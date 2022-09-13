// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyEnemy.generated.h"

UCLASS()
class GHOSTESCAPE_API AMyEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyEnemy();
	virtual void GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const override;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void EnemyLaugh();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	TObjectPtr<USoundBase> LaughSound;

	
	int32 EnemyLaughTime;
	FTimerHandle LaughTimerHandle;

	

	
	
	// Called to bind functionality to input
};
	