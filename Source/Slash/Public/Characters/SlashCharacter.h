// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "InputActionValue.h"
#include "Characters/CharacterTypes.h"
#include "Interfaces/PickUpInterface.h"
#include "SlashCharacter.generated.h"


class USlashOverlay;
class UInputAction;
class UInputMappingContext;
class UCameraComponent;
class USpringArmComponent;
class UGroomComponent;
class AItem;
class ASouls;
class UAnimMontage;
class ATreasure;


UCLASS()
class SLASH_API ASlashCharacter : public ABaseCharacter , public IPickUpInterface
{
	GENERATED_BODY()

public:

	ASlashCharacter();
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Jump() override;
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;
	virtual void SetOverlappingItem(AItem* Item) override;
	virtual void AddSouls( ASouls* Souls) override;
	virtual void AddGold(ATreasure* Gold) override;

protected:
	
	virtual void BeginPlay() override;
	
	
	
	 /** Inputs */
	
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> IMC_Slash;
	UPROPERTY(	EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> MovementAction;
	UPROPERTY(	EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> LookAction;
	UPROPERTY(	EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> JumpAction;
	UPROPERTY(	EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> EquipAction;
	UPROPERTY(	EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> AttackAction;
	UPROPERTY(	EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> DodgeAction;
	    
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Equip();
	bool IsOccupied();
	bool HasStamina();
	void Dodge();
	/*Combat*/
	virtual void Attack() override;
	virtual void DodgeEnd() override;
	virtual  bool CanAttack() override;
	
	void PlayEquipMontage(FName SectionName);
	virtual  void Die() override;
	

	UFUNCTION(BlueprintCallable)
	void Disarm();

	UFUNCTION(BlueprintCallable)
	void Arm();

	UFUNCTION(BlueprintCallable)
	void FinishEquipping();
	
	UFUNCTION(BlueprintCallable)
	void HitReactEnd();


private:
	void InitializeSlashOverlay(APlayerController* PlayerController);
	void SetHUDHealth();
	
	/*Character Components*/
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArm;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> ViewCamera;
	
	UPROPERTY(VisibleAnywhere ,Category = Hair)
	TObjectPtr<UGroomComponent> Hair;
	
	UPROPERTY(VisibleAnywhere,Category = Hair)
	TObjectPtr<UGroomComponent> EyeBrows;

	UPROPERTY(VisibleInstanceOnly)
	TObjectPtr<AItem> OverlappingItem;
	
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	TObjectPtr<UAnimMontage> EquipMontage;

	
	ECharacterState CharacterState = ECharacterState::ESC_Unequipped;
	
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess="true"))
	EActionState ActionState = EActionState:: EAS_Unoccupied;

	UPROPERTY()
	TObjectPtr<USlashOverlay> SlashOverlay;


	
	
public:
	
	
	FORCEINLINE ECharacterState GetCharacterState() const {return  CharacterState;}
	FORCEINLINE EActionState GetActionState() const {return ActionState;}
};
