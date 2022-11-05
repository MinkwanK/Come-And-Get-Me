// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "MyPlayerController.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenu::OnStartButtonClicked()
{
	UGameplayStatics::OpenLevel(this,FName("Stage1"));
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetOwningPlayer());

	if(PlayerController!=nullptr)
	{
		PlayerController->HideMainMenuWidget();
	}

}

void UMainMenu::OnExitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(this,GetOwningPlayer(),EQuitPreference::Quit,true);
}

void UMainMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if(StartButton!=nullptr)
	{
		StartButton->OnClicked.AddDynamic(this,&UMainMenu::OnStartButtonClicked);
		
	}
	if(ExitButton!=nullptr)
	{
		ExitButton->OnClicked.AddDynamic(this,&UMainMenu::OnExitButtonClicked);
	}
}


