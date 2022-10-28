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
	
	UPROPERTY()
	class UMainMenu* MainMenu;
	
	UPROPERTY()
	class UScaryGameOver* ScaryGameOverWidget;

	UPROPERTY()
	class UCrossHairWidget* CrossHairWidget;

	UPROPERTY()
	class UItemWidget* ItemWidget;

	
public:
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class URestartWidget> BP_RestartWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UMainMenu> BP_MainMenu;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UScaryGameOver> BP_ScaryGameOver;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UCrossHairWidget>BP_CrossHairWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UItemWidget>BP_ItemWidget;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	TObjectPtr<USoundBase> GameOverScarySound;

	





	void ShowRestartWidget();
	void HideRestartWidget();

	void ShowMainMenuWidget();
	void HideMainMenuWidget();

	void ShowScaryGameOverWidget();
	void HideScaryGameOverWidget();

	void ShowCrossHair();
	void HideCrossHair();

	void ShowItemWidget(AActor* Actor);
	void HideItemWidget();

	
	


	
	
	
	
	
};
