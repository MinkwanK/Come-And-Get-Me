// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_CivilianDead.h"

#include "MyCivilian.h"
#include "MyCivilianController.h"

EBTNodeResult::Type UMyBTTask_CivilianDead::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMyCivilianController* CivilianCon = Cast<AMyCivilianController>(OwnerComp.GetAIOwner());
	AMyCivilian* Civilian = Cast<AMyCivilian> (CivilianCon->GetPawn());

	Civilian->Destroy();

	FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
	
}

