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
	}
}

void URestartWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if(RestartButton != nullptr)
	{
		RestartButton->OnClicked.AddDynamic(this,&URestartWidget::OnRestartClicked);
	}
}

