// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class UNiagaraComponent;
class USphereComponent;

enum class EItemState : uint8
{
	EIS_Hovering,
	EIS_Equipped,
	EIS_NotHovering
	
};


UCLASS()
class SLASH_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual  void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
	float Amplitude = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
	float TimeConstant = 5.f;

	UFUNCTION(BlueprintPure)
	float TransformedSin();

	UFUNCTION(BlueprintPure)
	float TransformedCos();

	template<typename T>
	T Avg(T First, T Second);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    		TObjectPtr<UStaticMeshComponent>ItemMesh;

	
	EItemState ItemState = EItemState::EIS_Hovering;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraComponent> EmberEffect;
	

private:
	float RunningTime;

	
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<USphereComponent> Sphere;
};
template<typename T>
inline T AItem::Avg(T First, T Second)
{
	return (First + Second) / 2;
}