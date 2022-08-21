// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "RestartWidget.h"


void AMyPlayerController::ShowRestartWidget()
{
	if(BP_RestartWidget!= nullptr)
	{
		SetPause(true);
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
		RestartWidget = CreateWidget<URestartWidget>(this,BP_RestartWidget);
		RestartWidget->AddToViewport();
	}
	
}
void AMyPlayerController::HideRestartWidget()
{
	RestartWidget->RemoveFromParent();
	RestartWidget->Destruct();
	SetPause(false);
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
	
}


