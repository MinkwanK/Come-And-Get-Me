// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "NPCExitTargetPoint.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTESCAPE_API ANPCExitTargetPoint : public ATargetPoint
{
	GENERATED_BODY()


	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp,AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
};
