// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Treasure.h"
#include "Characters/SlashCharacter.h"
#include "Kismet/GameplayStatics.h"

ATreasure::ATreasure()
{
	 ItemState = EItemState::EIS_NotHovering;
}

void ATreasure::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASlashCharacter* SlashCharacter = Cast<ASlashCharacter>(OtherActor);
	
	if(SlashCharacter)
	{
		if(PickpSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this,PickpSound,GetActorLocation());
		}
		
		Destroy();
	}
}
