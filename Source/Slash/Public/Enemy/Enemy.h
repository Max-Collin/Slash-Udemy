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
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
private:
	/*
	* Components
	*/
	
	UPROPERTY(VisibleAnywhere)
	UHealthBarComponent* HealthBarWidget;
	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensing;
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

	EEnemyState EnemyState = EEnemyState::EES_Patrolling;
	UPROPERTY()
	AActor* CombatTarget;
	UPROPERTY(EditAnywhere)
	double CombatRadius = 1000.f;
	double AttackRadius = 200.f;
protected:
	virtual void BeginPlay() override;

	virtual void Die() override;
	bool InTargetRange(AActor* Target, double Radius);
	void MoveToTarget(AActor* Target);
	AActor* ChoosePatrolTarget();
	UFUNCTION()
	void PawnSeen(APawn* SeenPawn);
	
	UPROPERTY(BlueprintReadOnly)
	EDeathPose DeathPose = EDeathPose::EDP_Alive;
public:	
	
};