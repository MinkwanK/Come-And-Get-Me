// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HealthComponent.h"
#include "MyEnemy.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	IDLE UMETA(DisplayName = "IDLE"),
	Dead UMETA(DisplayName = "Dead"),
};

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

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UHealthComponent> HealthComp;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	TObjectPtr<USoundBase> LaughSound;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EEnemyState EnemyStateEnum;


	void EnemyLaugh();
	void Dead();
	
	int32 EnemyLaughTime;
	FTimerHandle LaughTimerHandle;

	

	private:
	
	// Called to bind functionality to input
};
	