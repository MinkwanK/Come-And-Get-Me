// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTESCAPE_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	class UButton* StartButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ExitButton;

public:
	virtual void NativeOnInitialized() override;
protected:
	UFUNCTION()
	void OnStartButtonClicked();
	UFUNCTION()
	void OnExitButtonClicked();
	
};
