// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "Camera/CameraComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/Character.h"

#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Sight.h"
#include "MyCharacter.generated.h"


UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	IDLE UMETA(DisplayName = "IDLE"),
	AIM UMETA(DisplayName = "AIM"),
};

UCLASS()
class GHOSTESCAPE_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();


	// 0 : 기본상태  1: 공격상태  2: 에임
	

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAIPerceptionStimuliSourceComponent> AIPerceptionStimuliSourceComp;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite);
	TObjectPtr<USpotLightComponent> PlayerLightComp;

	UPROPERTY(VisibleAnywhere);
	TObjectPtr<UPawnNoiseEmitterComponent> NoiseEmitterComp;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	TObjectPtr<UAnimMontage> AimMontage;
	


	//UClass에 안전성을 추가한 것이다.
	TSubclassOf<UAISense_Sight> Sight;
	TSubclassOf<UAISense_Hearing>Hearing;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	TObjectPtr<USoundBase> AttackSound;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EPlayerState PlayerStateEnum;
	
	class UAISenseConfig_Sight* SenseSight;
	
	FTimerHandle GameOverScaryWidget_TimerHandle;
	FTimerHandle AttackTimerHandle;
	FTimerHandle TargetFoundTimerHandle;

	int AttackTime;
	int TargetFoundTime;
	
	int GameOverScaryWidgetTimer;

	float MaxMovementNoiseRange;

	bool bCanSeeCivilian;

	bool bDetectItem;

	
	void AttackTimeLoss();
	void TargetFoundTimeLoss();



	
	



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



	void LightOn();
	void Attack();
	void Run();
	void StopRun();
	void Interact();
	void Aim();
	void NotAim();
	
	UFUNCTION()
	void ActiveCrouch();
	
	void MoveRight(float Value);
	void MoveForward(float Value);

	
	
private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "MyFPS_Cam", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FPS_Camera;



	


	bool bDead;
	bool bLight;
	bool bShowItemWidget = false;

	void PlayerDead();
	


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	
	
	void GameOverScaryWidget_TimeLoss();

	

};
