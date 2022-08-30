 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScaryGameOver.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTESCAPE_API UScaryGameOver : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UImage* ScaryImage;

	public:
	virtual void NativeOnInitialized() override;
};
