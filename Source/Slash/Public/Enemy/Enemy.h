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
	
	virtual void Tick(float DeltaTime) override;
	void CheckPatrolTarget();
	
	void CheckCombatTarget();

	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void Destroyed() override;


private:
	
	
	UPROPERTY(VisibleAnywhere)
	UHealthBarComponent* HealthBarWidget;
	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensing;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon> WeaponCLass;
	
	/**
	* Animation montages
	*/
	



	
	/** 
	* Navigation
	*/
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
	void PatrolTimerFinished();
	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float WaitMin = 1.f;
	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float WaitMax = 5.f;
	
	
	
	UPROPERTY()
	AActor* CombatTarget;
	UPROPERTY(EditAnywhere)
	double CombatRadius = 1000.f;
	double AttackRadius = 200.f;

	// AI Behavior
	void HideHealthbar();
	void ShowHealthBar();
	void LoseIntrest();
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

	//Combat
	void StartAttackTimer();
	void ClearAttackTimer();
	
	FTimerHandle AttackTimer;

	UPROPERTY(EditAnywhere , Category = Combat)
		float AttackMin = 0.5f;
	UPROPERTY(EditAnywhere , Category = Combat)
		float AttackMax = 1.5f;
	
	UPROPERTY(EditAnywhere , Category = Combat)
	float PatrolSpeed=125.f;
	UPROPERTY(EditAnywhere , Category = Combat)
	float ChaseSpeed=300.f;
	
protected:
	virtual void BeginPlay() override;

	virtual void Die() override;
	bool InTargetRange(AActor* Target, double Radius);
	void MoveToTarget(AActor* Target);
	AActor* ChoosePatrolTarget();
	virtual void Attack() override;
	virtual bool CanAttack() override;
	virtual  void HandleDamage(float DamageAmount) override;
	UFUNCTION()
	void PawnSeen(APawn* SeenPawn);
	virtual int32 PlayDeathMontage() override;

	UPROPERTY(EditAnywhere , Category = Combat)
	float DeathLifeSpan = 8.f;

	
	UPROPERTY(BlueprintReadOnly)
		TEnumAsByte<EDeathPose>  DeathPose;

	UPROPERTY(BlueprintReadOnly)
	EEnemyState EnemyState = EEnemyState::EES_Patrolling;
public:	
	
};