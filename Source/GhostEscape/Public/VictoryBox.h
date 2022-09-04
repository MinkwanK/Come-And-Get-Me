// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VictoryBox.generated.h"

UCLASS()
class GHOSTESCAPE_API AVictoryBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVictoryBox();

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp,AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category=VictoryBox,meta=(AllowPrivateAccess = "true"))
	class USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category=VictoryBox,meta=(AllowPrivateAccess = "true"))
	class UBoxComponent* CollisionBox;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
