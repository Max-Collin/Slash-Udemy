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
	virtual  bool CanAttack();
	bool IsAlive();
	void  DisableCapsule();
	

	/**
	 *Play Montage functions
	 */
	
	void PlayHitReactMontage(const FName& SectionName);
	void DirectionalHitReact(const FVector& ImpactPoint);
	void PlayMontageSection(TObjectPtr<UAnimMontage> Montage, const FName& SectionName);
	int32 PlayRandomMontageSetion(TObjectPtr<UAnimMontage> Montage,const TArray<FName>& SectionNames);
	virtual  int32 PlayDeathMontage();
	virtual  int32 PlayAttackMontage();



	
	void PlayHitSound(const FVector& ImpactPoint);
	void SpawnHitPartilces (const FVector& ImpactPoint);

	virtual void HandleDamage(float DamageAmount);
	
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
	UPROPERTY(EditAnywhere,Category = combat)
		TArray<FName> AttackMontageSections;

	UPROPERTY(EditAnywhere,Category = combat)
	TArray<FName> DeathMontageSections;
	
	/*
	* Components
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAttributeComponent> Attributes;
private:
		
	UPROPERTY(EditAnywhere, Category = Sounds)
	USoundBase* HitSound;
	UPROPERTY(EditAnywhere, Category = VisualEffects)
	UParticleSystem* HitParticles;

public:	
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled);

	
	

};




