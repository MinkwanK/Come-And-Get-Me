// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Hearing.h"

#include "MyCivilianController.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTESCAPE_API AMyCivilianController : public AAIController
{
	GENERATED_BODY()

public:
	AMyCivilianController();

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComponent; }

	UFUNCTION()
	void OnTargetPerception(AActor* Actor, FAIStimulus Stimulus); //인지된 하나의 타겟 액터만 리턴한다.



	class UAISenseConfig_Sight* Sight; 
	class UAISenseConfig_Hearing* Hearing;


	
	bool FirstGotDamage;
	int32 TargetLossCnt;
	FTimerHandle TargetLossTimerHandle;
	void TargetLoss();



	
	
protected:

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditAnywhere,Category=Damage)
	int Damage = 30;
	

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBehaviorTree> BehaviorTree;

	
	//BehaviorTree Reference
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

	//Blackboard Component Reference
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBlackboardComponent> BlackboardComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;

	
};
