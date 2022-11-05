// Fill out your copyright notice in the Description page of Project Settings.
//Player의 ItemSystem에 관한 소스파일입니다.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemSystem.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GHOSTESCAPE_API UItemSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemSystem();

	bool Pistol;
	bool Rifle;
	bool BookStack;
	int PistolAmmo;
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	
private:


	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
