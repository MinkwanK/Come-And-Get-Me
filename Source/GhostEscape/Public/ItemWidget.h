// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTESCAPE_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()

	public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemTxt;
	
	//virtual void NativeOnInitialized() override;



	

	
};
