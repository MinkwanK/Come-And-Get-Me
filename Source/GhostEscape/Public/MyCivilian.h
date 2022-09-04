// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCivilian.generated.h"

UCLASS()
class GHOSTESCAPE_API AMyCivilian : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCivilian();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
