// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EnemyAIController.h"
#include "BotTargetPoint.h"
#include "BTTargetPointSelection.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTESCAPE_API UBTTargetPointSelection : public UBTTaskNode
{
	GENERATED_BODY()

public:
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
