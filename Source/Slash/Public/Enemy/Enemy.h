// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HitInterface.h"
#include "Characters/CharacterTypes.h"

#include "Enemy.generated.h"


class UHealthBarComponent;

class UAttributeComponent;
class UAnimMontage;
class UPawnSensingComponent;

UCLASS()
class SLASH_API AEnemy : public ACharacter , public IHitInterface
{
	GENERATED_BODY()

public:
	
	AEnemy();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void DirectionalHitReact(const FVector& ImpactPoint);

	virtual void GetHit_Implementation(const FVector& ImpactPoint) override ;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
protected:

	virtual void BeginPlay() override;

	void Die();
	bool InTargetRange(TObjectPtr<AActor> Target, double Radius);
	void MovetoTarget(TObjectPtr<AActor> Target);
	TObjectPtr<AActor> ChoosePatrolTarget();
	
	UFUNCTION()
		void PawnSeen(APawn* SeenPawn);


	
	/**
	 *Play Montage functions
	 */
	void PlayHitReactMontage(const FName& SectionName);
	
	UPROPERTY(BlueprintReadOnly)
	EDeathPose DeathPose = EDeathPose::EDP_Alive;
	
private:

	/*
	 *Components
	 */
	
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UAttributeComponent> Attributes;
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UHealthBarComponent> HealthBarWidget;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPawnSensingComponent> PawnSensing;
	
	
	/**
	 * Animation montages
	 */
	UPROPERTY(EditDefaultsOnly, Category = Montages)
		TObjectPtr<UAnimMontage> HitReactMontage;

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	TObjectPtr<UAnimMontage> DeathMontage;
	
	UPROPERTY(EditAnywhere, Category = Sound)
		TObjectPtr<USoundBase> HitSound;

	UPROPERTY(EditAnywhere, Category = VisualEffects)
		TObjectPtr<UParticleSystem> HitParticles;

	

	/**
	 * Navigation
	 */

	UPROPERTY()
		class AAIController* EnemyController;
	//current patrol target
	UPROPERTY(EditInstanceOnly, Category="AI Navigation")
		TObjectPtr<AActor> PatrolTarget;
	//array of patrol targets
	UPROPERTY(EditInstanceOnly, Category="AI Navigation")
		TArray<TObjectPtr<AActor>> PatrolTargets;
	UPROPERTY(EditAnywhere)
		double CombatRadius=500.f;
	UPROPERTY(EditAnywhere)
		double PatrolRadius=1000.f;
	UPROPERTY()
		TObjectPtr<AActor> CombatTarget;
	FTimerHandle PatrolTimer;
	void PatrolTimerFinished();

	EEnemyState EnemyState = EEnemyState::EES_Patrolling;
	
public:	
		

};
