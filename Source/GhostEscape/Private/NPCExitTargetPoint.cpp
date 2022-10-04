// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCExitTargetPoint.h"
#include "MyCivilianController.h"
#include "MyCivilian.h"




//콜라이전 충돌 했을 때!
void ANPCExitTargetPoint::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMyCivilian* Civilian = Cast<AMyCivilian>(OtherActor);


	if(Civilian)
	{
		OtherActor->Destroy();
	}
}

