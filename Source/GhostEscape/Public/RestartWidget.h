// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RestartWidget.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTESCAPE_API URestartWidget : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(meta = (BindWidget))
	class UButton* RestartButton;

public:
	virtual void NativeOnInitialized() override;
protected:
	UFUNCTION()
	void OnRestartClicked();
	
};
