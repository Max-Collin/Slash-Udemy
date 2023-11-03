// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HitInterface.h"

#include "BaseCharacter.generated.h"

class AWeapon;
class UAttributeComponent;
class UAnimMontage;

UCLASS()
class SLASH_API ABaseCharacter : public ACharacter , public IHitInterface
{
	GENERATED_BODY()

public:
	
	ABaseCharacter();

protected:
	
	virtual void BeginPlay() override;
	virtual void Attack();
	virtual void Die();

	/**
	 *Play Montage functions
	 */
	virtual void PlayAttackMontage();
	void PlayHitReactMontage(const FName& SectionName);
	void DirectionalHitReact(const FVector& ImpactPoint);


	
	UPROPERTY(VisibleAnywhere, Category = Weapon)
		TObjectPtr<AWeapon>EquipedWeapon;
	

	/**
	 * Animation montages
	 */
	UPROPERTY(EditDefaultsOnly, Category = Montages)
		TObjectPtr<UAnimMontage> AttackMontage;
	UPROPERTY(EditDefaultsOnly, Category = Montages)
		TObjectPtr<UAnimMontage> HitReactMontage;
	UPROPERTY(EditDefaultsOnly, Category = Montages)
		UAnimMontage* DeathMontage;
	/*
	* Components
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAttributeComponent> Attributes;

		
	UPROPERTY(EditAnywhere, Category = Sounds)
	USoundBase* HitSound;
	UPROPERTY(EditAnywhere, Category = VisualEffects)
	UParticleSystem* HitParticles;

public:	
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled);

	
	

};
