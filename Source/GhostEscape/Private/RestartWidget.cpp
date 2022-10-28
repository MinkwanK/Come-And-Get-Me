// Fill out your copyright notice in the Description page of Project Settings.


#include "RestartWidget.h"
#include "MyPlayerController.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void URestartWidget::OnRestartClicked()
{
	UGameplayStatics::OpenLevel(this,FName(*UGameplayStatics::GetCurrentLevelName(this)));
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetOwningPlayer());

	if(PlayerController!=nullptr)
	{
		PlayerController->HideRestartWidget();
		PlayerController->ShowCrossHair();
	}
}

void URestartWidget::OnMenuButtonClicked()
{
	UGameplayStatics::OpenLevel(this,FName("StartMap"));
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetOwningPlayer());

	if(PlayerController != nullptr)
	{
		PlayerController->ShowMainMenuWidget();
	}
}


void URestartWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if(RestartButton != nullptr)
	{
		RestartButton->OnClicked.AddDynamic(this,&URestartWidget::OnRestartClicked);
	}
	if(MenuButton != nullptr)
	{
		MenuButton->OnClicked.AddDynamic(this,&URestartWidget::OnMenuButtonClicked);
	}
}

