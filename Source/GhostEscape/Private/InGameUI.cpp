// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI.h"

#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UInGameUI::UpdateHorrorScoreTxt(int HorrorScore)
{
	HorrorScoreTxt->SetText(FText::AsNumber(HorrorScore));
}


