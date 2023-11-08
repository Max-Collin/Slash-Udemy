// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include  "Characters/BaseCharacter.h"
#include "Characters/CharacterTypes.h"

#include "Enemy.generated.h"



class UHealthBarComponent;
class UPawnSensingComponent;

UCLASS()
class SLASH_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AEnemy();
	/* <AActor> */
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Destroyed() override;
	/* </AActor> */
	
	/* <IHitInterface> */
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;
	/* </IHitInterface> */
protected:
	/* <AActor> */
	virtual void BeginPlay() override;
	/* </AActor> */

	/* <ABaseCharacter> */
	virtual void Die() override;
	virtual void Attack() override;
	virtual bool CanAttack() override;
	virtual  void HandleDamage(float DamageAmount) override;
	virtual void AttackEnd() override;
	/* </ABaseCharacter> */
	
	
	

	UPROPERTY(BlueprintReadOnly)
	EEnemyState EnemyState = EEnemyState::EES_Patrolling;
	
	
private:
	/* AI Behavior */
	void CheckPatrolTarget();
	void CheckCombatTarget();
	void PatrolTimerFinished();
	void SpawnDefaultWeapon();
	void HideHealthBar();
	void ShowHealthBar();
	void LoseInterest();
	void StartPatrolling();
	void ChaseTarget();
	bool IsOutsideCombatRadius();
	bool IsOutsideAttackRadius();
	bool IsInsideAttackRadius();
	bool IsChasing();
	bool IsAttacking();
	bool IsDead();
	bool IsEngaged();
	void ClearPatrolTimer();
	void StartAttackTimer();
	void ClearAttackTimer();
	bool InTargetRange(AActor* Target, double Radius);
	void MoveToTarget(AActor* Target);
	AActor* ChoosePatrolTarget();
	
	UFUNCTION()
	void PawnSeen(APawn* SeenPawn);
	
	UPROPERTY(VisibleAnywhere)
	UHealthBarComponent* HealthBarWidget;
	
	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensing;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon> WeaponCLass;
	

	
	UPROPERTY(EditAnywhere)
	double CombatRadius = 1000.f;
	
	double AttackRadius = 200.f;
	
	UPROPERTY()
	class AAIController* EnemyController;
	
	// Current patrol target
	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	AActor* PatrolTarget;
	
	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	TArray<AActor*> PatrolTargets;
	
	UPROPERTY(EditAnywhere)
	double PatrolRadius = 2000.f;
	
	FTimerHandle PatrolTimer;
	
	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrolWaitMin = 1.f;
	
	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrolWaitMax = 5.f;

		
	UPROPERTY(EditAnywhere , Category = Combat)
	float PatrolSpeed=125.f;

	FTimerHandle AttackTimer;

	UPROPERTY(EditAnywhere , Category = Combat)
	float AttackMin = 0.25f;
	
	UPROPERTY(EditAnywhere , Category = Combat)
	float AttackMax = 0.75f;
	
	UPROPERTY(EditAnywhere , Category = Combat)
	float ChaseSpeed=300.f;

	UPROPERTY(EditAnywhere , Category = Combat)
	float DeathLifeSpan = 8.f;


public:	
	
};