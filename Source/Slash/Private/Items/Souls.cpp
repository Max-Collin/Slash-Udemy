// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Souls.h"

#include "NiagaraFunctionLibrary.h"
#include "Interfaces/PickUpInterface.h"

void ASouls::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IPickUpInterface* PickUpInterface = Cast<IPickUpInterface>(OtherActor);
	
	if(PickUpInterface)
	{
		PickUpInterface->SetOverlappingItem(this);
		PickUpInterface->AddSouls(this);

		if(PickupEffect)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,PickupEffect,GetActorLocation());
			SpawnPickupSound();
		}
		Destroy();
	}
	
}
