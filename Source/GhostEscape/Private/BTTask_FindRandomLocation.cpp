// Fill out your copyright notice in the Description page of Project Settings.
//Find Random Location Task

#include "BTTask_FindRandomLocation.h"

#include "MyCivilian.h"
#include "MyCivilianController.h"
#include "NavigationSystem.h"

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMyCivilianController* CivilianCon = Cast<AMyCivilianController>(OwnerComp.GetAIOwner());

	
		UBlackboardComponent* BlackboardComponent = CivilianCon->GetBlackboardComp();
		AMyCivilian* Civilian = Cast<AMyCivilian> (CivilianCon->GetPawn());
		FVector CivilianLoc = Civilian->GetActorLocation();
		FNavLocation RandomLocation{};
		//Navigable Data

		//obtain navigation system
		const UNavigationSystemV1* NavSystem{UNavigationSystemV1::GetCurrent(GetWorld())};
		if(IsValid(NavSystem) && NavSystem->GetRandomPointInNavigableRadius(CivilianLoc,SearchRadius,RandomLocation))
		{
			CivilianCon->GetBlackboardComp()->SetValueAsVector(BlackboardKey.SelectedKeyName,RandomLocation.Location);
		}
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	
}
