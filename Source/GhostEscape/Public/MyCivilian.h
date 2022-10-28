// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCivilian.generated.h"

UCLASS()
class GHOSTESCAPE_API AMyCivilian : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCivilian();
	


	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	TObjectPtr<USoundBase> IdleSound;

		
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	TObjectPtr<USoundBase> ScaredSound;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	bool CanSeePlayer;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	bool CanHear;


	
	
	virtual void GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const override;
	
	bool state[3]; //0 평시 1 소리듣기 2 적 발견
	
	int32 ScaredSoundCnt;
	FTimerHandle ScaredSoundTimerHandle;
	void SoundCntLoss();


	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	class UHealthComponent* HealthComponent;

};
