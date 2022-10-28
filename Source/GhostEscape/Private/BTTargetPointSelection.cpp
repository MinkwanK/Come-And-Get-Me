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
			//랜덤 타겟 포인트 정하기
			RandomIndex = FMath::RandRange(0,AvailableTargetPoints.Num()-1);
			NextTargetPoint = Cast<ABotTargetPoint>(AvailableTargetPoints[RandomIndex]);

			//이미 직전에 방문했다면, 다시 정하기
			if(NextTargetPoint->VisitedCnt == 1)
				continue;

			//직전에 방문하지 않은 타겟 포인트라면 방문 표시
			NextTargetPoint->VisitedCnt = 1; 
		}
		//새로운 타겟 포인트를 찾을 때 까지
		while (CurrentPoint == NextTargetPoint);

		BlackboardComp->SetValueAsObject("LocationToGo", NextTargetPoint);
		//이 시점에선, 테스크는 성공적으로 완수된다.
		return EBTNodeResult::Succeeded;
		
	}
	return EBTNodeResult::Failed;
}