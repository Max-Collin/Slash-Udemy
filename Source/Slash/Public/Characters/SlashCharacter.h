// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "Characters/CharacterTypes.h"
#include "SlashCharacter.generated.h"


class AWeapon;
class UInputAction;
class UInputMappingContext;
class UCameraComponent;
class USpringArmComponent;
class UGroomComponent;
class AItem;
class UAnimMontage;






UCLASS()
class SLASH_API ASlashCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASlashCharacter();

	UFUNCTION(BlueprintCallable)
	void SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**
	 * Inputs
	 */

	
	
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
	    
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Equip();
	void Attack();

	
	/**
	 *Play Montage functions
	 */
	void PlayAttackMontage();
	void PlayEquipMontage(FName SectionName);

	UFUNCTION(BlueprintCallable)
	void Disarm();

	UFUNCTION(BlueprintCallable)
	void Arm();

	UFUNCTION(BlueprintCallable)
	void FinishEquipping();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Jump() override;
private:
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

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	TObjectPtr<AWeapon>EquipedWeapon;

	/**
	 * Animaation montages
	 */
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	TObjectPtr<UAnimMontage> AttackMontage;
	UPROPERTY(EditDefaultsOnly, Category = Montages)
    	TObjectPtr<UAnimMontage> EquipMontage;

	
	ECharacterState CharacterState = ECharacterState::ESC_Unequipped;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess="true"))
	EActionState ActionState = EActionState:: EAS_Unoccupied;
public:
	FORCEINLINE void SetOverlappingItem(TObjectPtr<AItem> Item){OverlappingItem=Item;}
	
	FORCEINLINE ECharacterState GetCharacterState() const {return  CharacterState;}
};
