// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyEnemy.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionTypes.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTESCAPE_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();

	FORCEINLINE TArray<AActor*> GetAvailableTargetPoints() {return BotTargetPoints;}

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComponent; }

	UPROPERTY(VisibleAnywhere)
	class AMyEnemy* Agent;

	UFUNCTION()
	void OnTargetPerception(AActor* Actor, FAIStimulus Stimulus); //인지된 하나의 타겟 액터만 리턴한다.

	//UFUNCTION()
	//void OnPerception(TArray<AActor*> const& UpdatedActors); //여러개의 액터를 받을때


	
	class UAISenseConfig_Sight* Sight; //시야 감각을 위함.
	class UAISenseConfig_Hearing* Hearing;

protected:
	
	/* 가상함수란?
	virtual은 가상함수이다. 부모클래스에서 상속받을 자식 클래스에서 재정의 할 것을 기대하고 정의한 함수입니다.
	가상함수를 사용하는 이유? 컴파일러가 함수 호출 코드는 컴파일 타임에 고정된 메모리 주소로 변환시킴 -> 정적바인딩
	컴파일 당시 호출될 함수의 번지가 이미 결정나서 원하는 함수의 동작이 안나올 수도 있음 따라서 가상함수를 사용하여 동적 바인딩을 한다.
	*/

	
	virtual void BeginPlay() override;
	

	//우리가 컨트롤하고 싶은 액터가 스폰되면 이 함수가 실행된다. 이 함수안에서 블랙보드와 비헤비어트리를 초기화 합니다.
	
	virtual void OnPossess(APawn* InPawn) override;

	//virtual void GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const override;

	void TargetLoss();

private:
	/*
	 
	EditDefaultsOnly 에서 Defaults 는 클래스의 디테일 창을 말하는 것이고 Instance는 월드 아웃 라이너의 애셋을 클릭했을 때의 디테일 창
	TObjectPtr 은 UE5로 넘어오면서 Raw 포인터 대신에 사용하는 것이다. 파라미터를 함수에 전달하거나 로컬 변수에 데이터를 저장하는 등과 같은 대부분의 경우에
	ObjectPtr은 자동으로 원시 포인터 타입으로 변환된다.
	RawPointer(원시 포인터)는 스마트 포인터와 같은 캡슐화 개체에 의해 수명이 제어되지 않는 포인터입니다. 원시 포인터는 다른 비포인터 변수의 주소를 할당하거나
    값을 nullptr 할 수 있습니다. 값이 할당되지 않은 포인터에는 임의 포인터가 드갑니다. 포인터를 역참조하여 포인터가 가리키는 개체의 값 검색 가능합니다.

	*/


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBehaviorTree> BehaviorTree;

	
	//BehaviorTree Reference
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

	//Blackboard Component Reference
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBlackboardComponent> BlackboardComponent;

	//Blackboard Key
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName LocationToGoKey;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;

	TArray<AActor*> BotTargetPoints;
	bool bCanSeeTarget;
	int32 TargetLossCnt;
	FTimerHandle TargetLossTimerHandle;

	
	





};
