// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HitInterface.h"

#include "Enemy.generated.h"

class UAnimMontage;

UCLASS()
class SLASH_API AEnemy : public ACharacter , public IHitInterface
{
	GENERATED_BODY()

public:
	
	AEnemy();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void DirectionalHitReact(const FVector& ImpactPoint);

	virtual void GetHit(const FVector& ImpactPoint) override;
protected:

	virtual void BeginPlay() override;

	
	/**
	 *Play Montage functions
	 */
	void PlayHitReactMontage(const FName& SectionName);

	
private:

	/**
	 * Animaation montages
	 */
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	TObjectPtr<UAnimMontage> HitReactMontage;
	
public:	
	

};
