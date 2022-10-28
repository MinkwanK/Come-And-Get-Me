// Fill out your copyright notice in the Description page of Project Settings.
//평범한 귀신 헌터를 위한 ai 컨트롤러입니다.
//AI컨트롤러는 비헤비어트리와 블랙보드와 상호작용하며, 자신과 연결된 모든 캐릭터에게 명령을 내림

#include "EnemyAIController.h"
#include "BotTargetPoint.h"
#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AISenseConfig_Hearing.h"

AEnemyAIController::AEnemyAIController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component"));
	

	LocationToGoKey = "LocationToGo";

	
	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	Sight->SightRadius = 2000.0f;
	Sight->LoseSightRadius = Sight->SightRadius + 500.0f;
	Sight->PeripheralVisionAngleDegrees = 90.0f; //좌우 시야 반경
	Sight->DetectionByAffiliation.bDetectNeutrals = true;
	

	Hearing = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));
	
	Hearing->HearingRange = 2000.0f;

	
	Hearing->DetectionByAffiliation.bDetectNeutrals = true;
	Hearing->DetectionByAffiliation.bDetectFriendlies = true;
	
	
	
	//DetectionByAffiliation 는 적 ,중립 ,아군이 이 이 감각을 작동시킬 수 있는지?
	//중립이 이 감각에 감지된다.

	AIPerceptionComponent->ConfigureSense(*Sight);
	AIPerceptionComponent->ConfigureSense(*Hearing);



	bCanSeeTarget = true;
	TargetLossCnt = 3;

	
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	
	AMyEnemy* Enemy = Cast<AMyEnemy>(GetPawn()); //현재 소유한 캐릭터가 적 클래스가 맞는지 확인합니다.
	if (IsValid(BehaviorTree.Get()))
	{
		RunBehaviorTree(BehaviorTree.Get());
		BehaviorTreeComponent->StartTree(*BehaviorTree.Get());
	}
	if(Enemy)
	{
		Agent = Enemy; //한명의 플레이어만 타겟으로 삼지 않나?!
	}

	
}


void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (IsValid(Blackboard.Get()) && IsValid(BehaviorTree.Get()))
	{
		Blackboard->InitializeBlackboard(*BehaviorTree.Get()->BlackboardAsset.Get());
	}
	
	//사용 가능한 NPC이동 지점을 배열에 채웁니다.
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ABotTargetPoint::StaticClass(),BotTargetPoints);
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this,&AEnemyAIController::OnTargetPerception);
	//AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this,&AEnemyAIController::OnPerception);

	
}



//적이 Actor를 인지했을 때
void AEnemyAIController::OnTargetPerception(AActor* Actor, FAIStimulus Stimuls)
{
	//매개변수로 받은 Actor를 Player로 형 변환
	AMyCharacter* Player = Cast<AMyCharacter>(Actor);
	//인지된 Actor가 Player가 아니라면
	if(Player == nullptr)
	{
		UE_LOG(LogTemp,Log,TEXT("Target percetion failed"));
		//AIController가 소유한 Pawn을 AMyEnemy로 형 변환
		AMyEnemy* Enemy = Cast<AMyEnemy>(GetPawn());
		//Player가 인지되지 않으면 속도를 내린다.
		Enemy->GetCharacterMovement()->MaxWalkSpeed = 300.0f;
		
		return; 
	}
	else 
	{   //Player를 인지할 때마다 호출
		UE_LOG(LogTemp,Log,TEXT("Target percetion success"));
		//인지된 자극의 Tag가 Noise 라면 -> 인지된 자극이 Player의 소리
		if(Stimuls.Tag == "Noise") 
		{
			//인지된 자극이 소리일 때, 블랙보드 키 값에 소리의 위치를 갱신
			BlackboardComponent->SetValueAsVector("TargetLocation",Player->GetActorLocation()); 
		}
		else
		{
			//인지된 자극이 소리가 아니라면, 블랙보드 키 값에 Player Object를 갱신
			BlackboardComponent->SetValueAsObject("TargetPlayer",Player); 
		}
		//AIController가 소유한 Pawn 들고오기
		AMyEnemy* Enemy = Cast<AMyEnemy>(GetPawn()); 
		if(Enemy)
		{
			//Player를 인지 했으므로, Enemy의 속도를 높인다.
			Enemy->GetCharacterMovement()->MaxWalkSpeed = 550.0f;
			
			//목표 상실 시간
			TargetLossCnt  = 3;
			//목표 상실 타이머 시작
			GetWorldTimerManager().ClearTimer(TargetLossTimerHandle);
			GetWorldTimerManager().SetTimer(TargetLossTimerHandle,this,&AEnemyAIController::TargetLoss,1.0f,true);  
		}
		
	}
}
/*
void AEnemyAIController::OnPerception(TArray<AActor*> const& UpdatedActors)
{
	UE_LOG(LogTemp,Log,TEXT("Percetion Success"));
	for(int i =0; i< UpdatedActors.Num(); i++)
	{
		FActorPerceptionBlueprintInfo info;
		GetPerceptionComponent()->GetActorsPerception(UpdatedActors[i],info);
		UE_LOG(LogTemp,Log,TEXT("Percetion Success"));
		for(int j=0; j < info.LastSensedStimuli.Num();j++)
		{
			FAIStimulus const stim = info.LastSensedStimuli[j];
			if(stim.Tag == "Noise")
			{
				BlackboardComponent->SetValueAsVector("LocationToGo",stim.StimulusLocation);
			}
			
		}
	}
	
}
*/


void AEnemyAIController::TargetLoss()
{
	UE_LOG(LogTemp,Log,TEXT("TargetLoss Count"));
	
	TargetLossCnt--;
		if(TargetLossCnt<0)
		{
			AMyEnemy* Enemy = Cast<AMyEnemy>(GetPawn());
			Enemy->GetCharacterMovement()->MaxWalkSpeed = 300.0f;
			BlackboardComponent->SetValueAsObject("TargetPlayer",nullptr);
			GetWorldTimerManager().ClearTimer(TargetLossTimerHandle);
		}
}
	
	


	
	

