// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTESCAPE_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

	UPROPERTY()
	class URestartWidget* RestartWidget;
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class URestartWidget> BP_RestartWidget;

	void ShowRestartWidget();
	void HideRestartWidget();
	
	
	
	
};
