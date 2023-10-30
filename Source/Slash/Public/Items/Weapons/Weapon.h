// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Weapon.generated.h"

class UBoxComponent;
/**
 * 
 */
UCLASS()
class SLASH_API AWeapon : public AItem
{
	GENERATED_BODY()


public:
	AWeapon();
protected:
	virtual void BeginPlay() override;

	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual  void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintImplementableEvent)
		void CreateFields(const FVector& fieldLocation);
public:
	

	virtual void Tick(float DeltaSeconds) override;
	void AttachMeshToSocket(USceneComponent* InParent, FName InSocketName);

	void Equip(USceneComponent* InParent, FName InSocketName);
	
	TArray<TObjectPtr<AActor>> IgnoreActors;
private:
	
	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
		TObjectPtr<UBoxComponent> WeaponBox;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<USceneComponent> BoxTraceStart;
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<USceneComponent> BoxTraceEnd;

	

	
public:	
	
	FORCEINLINE TObjectPtr<UBoxComponent> GetWeaponBox() const {return WeaponBox; }
};
