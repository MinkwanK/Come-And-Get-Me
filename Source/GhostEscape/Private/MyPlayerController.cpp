// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"


#include "RestartWidget.h"
#include "MainMenu.h"
#include "ScaryGameOver.h"
#include "CrossHairWidget.h"
#include "ItemWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"



void AMyPlayerController::ShowCrossHair()
{
	if(BP_CrossHairWidget != nullptr)
	{
		CrossHairWidget = CreateWidget<UCrossHairWidget>(this,BP_CrossHairWidget);
		CrossHairWidget->AddToViewport();
	}
}

void AMyPlayerController::HideCrossHair()
{
	CrossHairWidget->RemoveFromParent();
	CrossHairWidget->Destruct();
}

void AMyPlayerController::ShowItemWidget(AActor* Actor)
{
	if(BP_ItemWidget != nullptr)
	{
		if(Actor != nullptr)
		{
			
			ItemWidget = CreateWidget<UItemWidget>(this,BP_ItemWidget);
			ItemWidget->ItemTxt->SetText(FText::FromString(Actor->GetActorNameOrLabel()));
			ItemWidget->AddToViewport();
		}
	}
}

void AMyPlayerController::HideItemWidget()
{
	if(BP_ItemWidget!=nullptr)
	{
	
		ItemWidget->RemoveFromParent();
		ItemWidget->Destruct();
	}
}





void AMyPlayerController::ShowRestartWidget()
{
	if(BP_RestartWidget != nullptr)
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
		//UGameplayStatics::PlaySound2D(this,GameOverScarySound,1,1,0,nullptr,nullptr,true);
	
		
		
	}
}

void AMyPlayerController::HideScaryGameOverWidget()
{
	ScaryGameOverWidget->RemoveFromParent();
	ScaryGameOverWidget->Destruct();
}








