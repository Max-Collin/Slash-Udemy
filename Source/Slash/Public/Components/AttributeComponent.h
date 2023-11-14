// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SLASH_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttributeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void RegenStamina(float DeltaTime);

private:
	//Current Health
	UPROPERTY(EditAnywhere,Category = "Actor Attributes")
		float Health=100;
	
	UPROPERTY(EditAnywhere,Category = "Actor Attributes")
		float MaxHealth=100;
	
	UPROPERTY(EditAnywhere,Category = "Actor Attributes")
	float Stamina=100;
	

	UPROPERTY(EditAnywhere,Category = "Actor Attributes")
	float MaxStamina=100;

	
	UPROPERTY(EditAnywhere,Category = "Actor Attributes")
	float DodgeCost=15.f;
	
	UPROPERTY(EditAnywhere,Category = "Actor Attributes")
	float StaminaRegenRate=8.f;
	
	UPROPERTY(EditDefaultsOnly,Category = "Actor Attributes")
	int32 Gold;
	
	UPROPERTY(EditDefaultsOnly,Category = "Actor Attributes")
	int32 Souls;
	
	

public:

	void ReceiveDamage(float Damage);
	void UseStamina(float StaminaCost);
	float GetHealthPercent();
	float GetStaminaPercent();
	bool IsAlive();
	void AddSouls(int32 NumberOfSouls);
	void AddGold(int32 NumberOfGold);
	FORCEINLINE int32 GetGold() const { return  Gold;}
	FORCEINLINE int32 GetSouls() const { return  Souls;}
	FORCEINLINE float GetDodgeCost() const {return DodgeCost;}
	FORCEINLINE float GetStamina() const {return Stamina;}
};
