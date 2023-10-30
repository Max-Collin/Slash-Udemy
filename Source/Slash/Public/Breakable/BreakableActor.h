// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/HitInterface.h"

#include "BreakableActor.generated.h"


class UCapsuleComponent;
class UGeometryCollectionComponent;

UCLASS()
class SLASH_API ABreakableActor : public AActor , public  IHitInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABreakableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UCapsuleComponent>	Capsule;
	
	UPROPERTY(VisibleAnywhere)
    		TObjectPtr<UGeometryCollectionComponent> GeometryCollection;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void GetHit_Implementation(const FVector& ImpactPoint) override ;

private:
	

	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class ATreasure>> TreasureClasses;
		
	bool bBroken = false;	
                                            	

};
