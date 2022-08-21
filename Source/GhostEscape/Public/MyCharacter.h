// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
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
	

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAIPerceptionStimuliSourceComponent> AIPerceptionStimuliSourceComp;

	//UClass에 안전성을 추가한 것이다.
	TSubclassOf<UAISense_Sight> Sight;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	TObjectPtr<USoundBase> AttackSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

	void Attack();
	void Run();
	void StopRun();
	
	UFUNCTION()
	void ActiveCrouch();
	
	void MoveRight(float Value);
	void MoveForward(float Value);

	int State; //캐릭터의 현재 상태
	// 0 : 기본상태 1: 공격상태 
	bool Invisible;

private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "MyFPS_Cam", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FPS_Camera;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=  "MyFps_Cam",meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;



	bool bDead;
	int InvisibleTime;

	void PlayerDead();
	void InvisibleTimeLoss();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	FTimerHandle InvisibleTimerHandle;

};
