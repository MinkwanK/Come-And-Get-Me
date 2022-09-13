// Fill out your copyright notice in the Description page of Project Settings.

//민간인 AI, 무작위 이동 또는 특정 행동을 하다가, 플레이어를 마주치면, 도망가거나 상호작용 행동 수행(웅크리기, 벌벌떨기)

#include "MyCivilianController.h"

#include "MyCharacter.h"
#include "MyEnemy.h"

AMyCivilianController::AMyCivilianController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component"));

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	Sight->SightRadius = 2000.0f;
	Sight->LoseSightRadius = Sight->SightRadius + 500.0f;
	Sight->PeripheralVisionAngleDegrees = 90.0f; //좌우 시야 반경
	Sight->DetectionByAffiliation.bDetectNeutrals = true;

	Hearing = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));
	Hearing->HearingRange = 2000.0f;
	Hearing->DetectionByAffiliation.bDetectNeutrals = true;
	Hearing->DetectionByAffiliation.bDetectFriendlies = true;

	AIPerceptionComponent->ConfigureSense(*Sight);
	AIPerceptionComponent->ConfigureSense(*Hearing);




}

void AMyCivilianController::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(BehaviorTree.Get()))
	{
		RunBehaviorTree(BehaviorTree.Get());
		BehaviorTreeComponent->StartTree(*BehaviorTree.Get());
	}
}

void AMyCivilianController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (IsValid(Blackboard.Get()) && IsValid(BehaviorTree.Get()))
	{
		Blackboard->InitializeBlackboard(*BehaviorTree.Get()->BlackboardAsset.Get());
	}

	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this,&AMyCivilianController::OnTargetPerception);
}

void AMyCivilianController::OnTargetPerception(AActor* Actor, FAIStimulus Stimulus)
{
	AMyCharacter* Player = Cast<AMyCharacter>(Actor);

	if(Player)
	{
		
	}
	else
	{
		
	}
}
