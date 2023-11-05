// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "InputActionValue.h"
#include "Characters/CharacterTypes.h"

#include "SlashCharacter.generated.h"



class UInputAction;
class UInputMappingContext;
class UCameraComponent;
class USpringArmComponent;
class UGroomComponent;
class AItem;
class UAnimMontage;


UCLASS()
class SLASH_API ASlashCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:

	ASlashCharacter();
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;
	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;

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
	    
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Equip();
	/*Combat*/
	virtual void Attack() override;
	virtual  bool CanAttack() override;
	void PlayEquipMontage(FName SectionName);

	UFUNCTION(BlueprintCallable)
	void Disarm();

	UFUNCTION(BlueprintCallable)
	void Arm();

	UFUNCTION(BlueprintCallable)
	void FinishEquipping();
	
	UFUNCTION(BlueprintCallable)
	void HitReactEnd();


private:
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
public:
	FORCEINLINE void SetOverlappingItem(TObjectPtr<AItem> Item){OverlappingItem=Item;}
	
	FORCEINLINE ECharacterState GetCharacterState() const {return  CharacterState;}
};
