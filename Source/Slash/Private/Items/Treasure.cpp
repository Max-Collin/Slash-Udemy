// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Treasure.h"
#include "Interfaces/PickUpInterface.h"


ATreasure::ATreasure()
{
	 ItemState = EItemState::EIS_NotHovering;
}

void ATreasure::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IPickUpInterface* PickUpInterface = Cast<IPickUpInterface>(OtherActor);
	
	if(PickUpInterface)
	{
		SpawnPickupSound();
		PickUpInterface->AddGold(this);
		Destroy();
	}
}
