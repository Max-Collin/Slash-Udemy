// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AttributeComponent.h"

#include "../../../../../../../../../Program Files/Epic Games/UE_5.3/Engine/Plugins/Importers/USDImporter/Source/ThirdParty/USD/include/pxr/base/tf/pxrTslRobinMap/robin_hash.h"

// Sets default values for this component's properties
UAttributeComponent::UAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void UAttributeComponent::RegenStamina(float DeltaTime)
{
	Stamina = FMath::Clamp(Stamina + StaminaRegenRate *DeltaTime,0.f,MaxStamina);
}

void UAttributeComponent::ReceiveDamage(float Damage)
{
	Health = FMath::Clamp(Health-Damage,0,MaxHealth);
	if(Health==0)
	{
		
	}
}

void UAttributeComponent::UseStamina(float StaminaCost)
{
	Stamina = FMath::Clamp(Stamina-StaminaCost,0.f,MaxStamina);
	
}

float UAttributeComponent::GetHealthPercent()
{
	return Health/MaxHealth;
}

float UAttributeComponent::GetStaminaPercent()
{
	return Stamina/MaxStamina;
}

bool UAttributeComponent::IsAlive()
{
	return Health>0.f;
}

void UAttributeComponent::AddSouls(int32 NumberOfSouls)
{
	Souls+= NumberOfSouls;
}

void UAttributeComponent::AddGold(int32 NumberOfGold)
{
	Gold+= NumberOfGold;
}

