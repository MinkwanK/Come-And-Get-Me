// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "MyCharacter.generated.h"

UCLASS()
class GHOSTESCAPE_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "MyFPS_Cam")
	TObjectPtr<UCameraComponent> FPS_Camera;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAIPerceptionStimuliSourceComponent> AIPerceptionStimuliSourceComp;

	//UClass에 안전성을 추가한 것이다.
	TSubclassOf<UAISense_Sight> Sight;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

	
	void Run();
	void StopRun();
	
	UFUNCTION()
	void ActiveCrouch();
	
	void MoveRight(float Value);
	void MoveForward(float Value);



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
