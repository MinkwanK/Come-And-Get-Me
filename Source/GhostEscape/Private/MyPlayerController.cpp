// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "InGameUI.h"
#include "RestartWidget.h"
#include "MainMenu.h"
#include "ScaryGameOver.h"
#include "Kismet/GameplayStatics.h"


void AMyPlayerController::ShowInGameUI()
{
	if(BP_InGameUI != nullptr)
	{
		InGameUI = CreateWidget<UInGameUI>(this,BP_InGameUI);
		InGameUI->AddToViewport();
		
	}
}



void AMyPlayerController::ShowRestartWidget()
{
	if(BP_RestartWidget != nullptr)
	{
		InGameUI->RemoveFromParent();
		InGameUI->Destruct();
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

void AMyPlayerController::ShowMainMenuWidget()
{
	if(BP_MainMenu != nullptr)
	{
		SetPause(true);
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
		MainMenu = CreateWidget<UMainMenu>(this,BP_MainMenu);
		MainMenu->AddToViewport();
	}
}

//메인 메뉴-> 바로 게임 시작
void AMyPlayerController::HideMainMenuWidget()
{
	SetPause(false);
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}

//게임 오버 놀래키는 장면
void AMyPlayerController::ShowScaryGameOverWidget()
{
	if(BP_ScaryGameOver != nullptr)
	{
		
		SetPause(false);
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = false;
		ScaryGameOverWidget = CreateWidget<UScaryGameOver>(this,BP_ScaryGameOver);
		ScaryGameOverWidget->AddToViewport();
		UGameplayStatics::PlaySound2D(this,GameOverScarySound,1,1,0,nullptr,nullptr,true);
	
		
		
	}
}

void AMyPlayerController::HideScaryGameOverWidget()
{
	ScaryGameOverWidget->RemoveFromParent();
	ScaryGameOverWidget->Destruct();
}








