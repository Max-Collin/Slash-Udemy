// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HitInterface.h"
#include "Characters/CharacterTypes.h"
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
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;
	virtual void Attack();
	virtual void Die();
	virtual  bool CanAttack();
	bool IsAlive();
	void  DisableCapsule();
	void DisableMeshCollision();
	
	UFUNCTION(BlueprintCallable)
	void SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled);
	
	UFUNCTION(BlueprintCallable)
	virtual void AttackEnd();
	UFUNCTION(BlueprintCallable)
	virtual void DodgeEnd();
	/**
	 *Play Montage functions
	 */
	void PlayHitReactMontage(const FName& SectionName);
	void DirectionalHitReact(const FVector& ImpactPoint);
	virtual  int32 PlayDeathMontage();
	virtual  int32 PlayAttackMontage();
	void PlayDodgeMontage();
	void StopAttackMontage();

	UFUNCTION(BlueprintCallable)
	FVector GetTranslationWarpTarget();

	UFUNCTION(BlueprintCallable)
	FVector GetRotationWarpTarget();


	void PlayHitSound(const FVector& ImpactPoint);
	void SpawnHitParticles (const FVector& ImpactPoint);

	virtual void HandleDamage(float DamageAmount);
	
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	TObjectPtr<AWeapon>EquippedWeapon;
	

	UPROPERTY(BluePrintReadOnly , Category = Combat)
	AActor* CombatTarget;

	UPROPERTY(EditAnywhere , Category = Combat)
	double WarpTargetDistance =100.f;

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EDeathPose>  DeathPose;
	/*
	* Components
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAttributeComponent> Attributes;
private:
	void PlayMontageSection(TObjectPtr<UAnimMontage> Montage, const FName& SectionName);
	int32 PlayRandomMontageSection(TObjectPtr<UAnimMontage> Montage,const TArray<FName>& SectionNames);
	
	UPROPERTY(EditAnywhere, Category = combat)
	USoundBase* HitSound;
	UPROPERTY(EditAnywhere, Category = combat)
	UParticleSystem* HitParticles;

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
	
	
	UPROPERTY(EditDefaultsOnly, Category = Combat)
	TObjectPtr<UAnimMontage> DodgeMontage;
public:	
	
	FORCEINLINE TEnumAsByte<EDeathPose> GetDeathPose() const {return DeathPose;}

	
	

};




