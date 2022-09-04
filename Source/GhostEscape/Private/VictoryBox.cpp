// Fill out your copyright notice in the Description page of Project Settings.


#include "VictoryBox.h"

#include "MyCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AVictoryBox::AVictoryBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));

	RootComponent = RootScene;

	CollisionBox->SetupAttachment(RootScene);
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this,&AVictoryBox::OnBeginOverlap);

	CollisionBox->SetBoxExtent(FVector(60.0f,60.0f,60.0f));
	CollisionBox->SetRelativeLocation(FVector(0.0f,0.0f,120.0f));
}

// Called when the game starts or when spawned
void AVictoryBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVictoryBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVictoryBox::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Cast<AMyCharacter>(OtherActor))
	{
		UE_LOG(LogTemp,Log,TEXT("END"));
		UKismetSystemLibrary::QuitGame(GetWorld(),nullptr,EQuitPreference::Quit,true);
	}
}


