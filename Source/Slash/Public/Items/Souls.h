// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"

#include "Souls.generated.h"

/**
 * 
 */
UCLASS()
class SLASH_API ASouls : public AItem
{
	GENERATED_BODY()
protected:
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:
	UPROPERTY(EditAnywhere)
	int32 NumOfSouls;
	
	UPROPERTY(EditAnywhere)
    TObjectPtr<class UNiagaraSystem> PickupEffect;

public:
	FORCEINLINE int32 GetSouls() const { return NumOfSouls;}
	FORCEINLINE void SetSouls(int32 NumberOfSouls) {NumOfSouls = NumberOfSouls;} 
};
