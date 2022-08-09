// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTargetPointSelection.h"

EBTNodeResult::Type UBTTargetPointSelection::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* AICon = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());

	//AI 컨트롤러가 유효하다면, NPC의 현재 포인트와 블랙보드 컴포넌트를 받아온다.
	//다음 포인트를 찾는다.
	if(AICon)
	{
		UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComponent();
		ABotTargetPoint* CurrentPoint = Cast<ABotTargetPoint>(BlackboardComp->GetValueAsObject("LocationToGo"));
		
		if(CurrentPoint != nullptr)
		{
			CurrentPoint = 0;
		}
	
		
		
		TArray<AActor*> AvailableTargetPoints = AICon->GetAvailableTargetPoints();

		int32 RandomIndex;

		ABotTargetPoint* NextTargetPoint = nullptr;

		//직전에 방문한 타겟포인트트는 방문하지 않는다.
		
		do
		{
			
			RandomIndex = FMath::RandRange(0,AvailableTargetPoints.Num()-1);
			NextTargetPoint = Cast<ABotTargetPoint>(AvailableTargetPoints[RandomIndex]);
			if(NextTargetPoint->VisitedCnt == 1)
				continue;
			NextTargetPoint->VisitedCnt = 1; 
		}
		while (CurrentPoint == NextTargetPoint);

		BlackboardComp->SetValueAsObject("LocationToGo", NextTargetPoint);
		//이 시점에선, 테스크는 성공적으로 완수된다.
		return EBTNodeResult::Succeeded;
		
	}
	return EBTNodeResult::Failed;
}