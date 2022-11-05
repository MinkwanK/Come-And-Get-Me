// Fill out your copyright notice in the Description page of Project Settings.

//민간인 AI, 무작위 이동 또는 특정 행동을 하다가, 플레이어를 마주치면, 도망가거나 상호작용 행동 수행(웅크리기, 벌벌떨기)

#include "MyCivilianController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyCharacter.h"
#include "MyCivilian.h"
#include "Kismet/GameplayStatics.h"


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



	TargetLossCnt = 1.5;
	//Civilian이 첫 데미지를 받았는지 여부이다 플레이어를 인지할 때마다 데미지가 들어오는 것을 방지하기 위함이다.
	FirstGotDamage = false;


	




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
	AMyCivilian* Civilian = Cast<AMyCivilian>(InPawn);
	
	
	
}

void AMyCivilianController::OnTargetPerception(AActor* Actor, FAIStimulus Stimulus)
{
	AMyCharacter* Player = Cast<AMyCharacter>(Actor);
	AMyCivilian* Civilian = Cast<AMyCivilian>(GetPawn());

	if(Player == nullptr)
	{
		//UE_LOG(LogTemp,Log,TEXT("Target percetion failed"));
		Civilian->GetCharacterMovement()->MaxWalkSpeed = 200.0f;
		return; 
	}
	else 
	{
	
		if(Stimulus.Tag == "Noise") //플레이어 소리
		{
			return; 
			/*
			Civilian->state[1] = true; //0 평시 1 소리듣기 2 적 발견
			Civilian->CanHear = true;
			BlackboardComponent->SetValueAsBool("CanHear",true); //인지된 액터가 플레이어면 키 값에 플레이어 업데이트
			BlackboardComponent->SetValueAsVector("TargetSoundLocation",Player->GetActorLocation());
			GetWorldTimerManager().ClearTimer(TargetLossTimerHandle);
			GetWorldTimerManager().SetTimer(TargetLossTimerHandle,this,&AMyCivilianController::TargetLoss,1.0f,true);
			*/
		}
	
		if(Stimulus.Tag == "AttackNoise") //플레이어의 공격
		{
			Civilian->state[1] = true; //0 평시 1 소리듣기 2 적 발견
			
			BlackboardComponent->SetValueAsBool("CanHear",true); //인지된 액터가 플레이어면 키 값에 플레이어 업데이트
			BlackboardComponent->SetValueAsVector("TargetSoundLocation",Player->GetActorLocation());
			GetWorldTimerManager().ClearTimer(TargetLossTimerHandle);
			GetWorldTimerManager().SetTimer(TargetLossTimerHandle,this,&AMyCivilianController::TargetLoss,1.0f,true); 
		}
		else
		{
			Civilian->state[2]=true;
			Civilian->CanSeePlayer = true;

			BlackboardComponent->SetValueAsObject("TargetPlayer",Player);
			//UE_LOG(LogTemp,Log,TEXT("Player percetion success"));
			Civilian->GetCharacterMovement()->MaxWalkSpeed = 400.0f;
			BlackboardComponent->SetValueAsBool("CanSeePlayer",true); //인지된 액터가 플레이어면 키 값에 플레이어 업데이트
			UE_LOG(LogTemp,Log,TEXT("Target Player Update Succeede"));
		
		}
		
		
	}
}

void AMyCivilianController::TargetLoss() //TargetSound Locaiton 인지 상실 타이머
{
	TargetLossCnt--;
	if(TargetLossCnt<0)
	{
		AMyCivilian* Civilian = Cast<AMyCivilian>(GetPawn());
		Civilian->state[1] = false;
		Civilian->CanHear = false;
		TargetLossCnt  = 3.0;
		BlackboardComponent->SetValueAsBool("CanHear",false);
		GetWorldTimerManager().ClearTimer(TargetLossTimerHandle);
	}
}

