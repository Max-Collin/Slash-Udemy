// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SlashCharacter.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GroomComponent.h"
#include "Characters/CharacterTypes.h"
#include "Items/Item.h"
#include  "items/Weapons/Weapon.h"
#include "Animation/AnimMontage.h"

// Sets default values
ASlashCharacter::ASlashCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate=FRotator(0.f,360.,0.f);

	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 300.f;
	
	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(SpringArm);
	
	Hair = CreateDefaultSubobject<UGroomComponent>(TEXT("Hair"));
	Hair->SetupAttachment(GetMesh());
	Hair->AttachmentName = FString("head");

	EyeBrows = CreateDefaultSubobject<UGroomComponent>(TEXT("EyeBrows"));
	EyeBrows->SetupAttachment(GetMesh());
	EyeBrows->AttachmentName = FString("head");
	
}

void ASlashCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC_Slash,0);
		}
	}

	Tags.Add(FName("Player"));
}

void ASlashCharacter::Move(const FInputActionValue& Value)
{
	if(ActionState !=EActionState::EAS_Unoccupied)return;
	const FVector2d MovementVector = Value.Get<FVector2d>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f,Rotation.Yaw,0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	AddMovementInput(ForwardDirection,MovementVector.Y);
	
	const FVector RightDirection =FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection,MovementVector.X);
}

void ASlashCharacter::Look(const FInputActionValue& Value)
{
	const FVector2d LookAxisVector = Value.Get<FVector2d>();

	AddControllerPitchInput(LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);
}

void ASlashCharacter::Equip()
{
	TObjectPtr<AWeapon> OverlappingWeapon = Cast<AWeapon>(OverlappingItem);
	if(OverlappingItem)
	{
		OverlappingWeapon->Equip(GetMesh(),FName("RightHandSocket"),this,this);
	
		CharacterState = ECharacterState::ESC_EquippedOneHandedWeapon;
		OverlappingItem =nullptr;
		EquippedWeapon = OverlappingWeapon;
		
		
	}
	else
	{
		if(ActionState == EActionState::EAS_Unoccupied && CharacterState != ECharacterState::ESC_Unequipped )
		{
			PlayEquipMontage(FName ("Unequip"));
			CharacterState=ECharacterState::ESC_Unequipped;
			ActionState = EActionState::EAS_EquippingWeapon;
			
			
		}
		else if(ActionState == EActionState::EAS_Unoccupied && CharacterState == ECharacterState::ESC_Unequipped &&EquippedWeapon)
		{
			PlayEquipMontage(FName ("Equip"));
			CharacterState=ECharacterState::ESC_EquippedOneHandedWeapon;

			ActionState = EActionState::EAS_EquippingWeapon;
		}
	}		
}

void ASlashCharacter::Attack()
{
	Super::Attack();
	if(CanAttack())
	{
		PlayAttackMontage();
		ActionState = EActionState::EAS_Attacking;
	}

}

bool ASlashCharacter::CanAttack()
{
	return  ActionState == EActionState::EAS_Unoccupied &&
		CharacterState != ECharacterState::ESC_Unequipped;
}


void ASlashCharacter::PlayEquipMontage(FName SectionName)
{
	TObjectPtr<UAnimInstance> AnimInstance = GetMesh()->GetAnimInstance();
	if(AnimInstance&&EquipMontage)
	{
		AnimInstance->Montage_Play(EquipMontage);
		AnimInstance->Montage_JumpToSection(SectionName,EquipMontage);
	}
}

void ASlashCharacter::Disarm()
{
	if(EquippedWeapon)
	{
		EquippedWeapon->AttachMeshToSocket(GetMesh(),FName("SpineSocket"));
	}
}

void ASlashCharacter::Arm()
{
	
	if(EquippedWeapon)
	{
		EquippedWeapon->AttachMeshToSocket(GetMesh(),FName("RightHandSocket"));
	}
}

void ASlashCharacter::FinishEquipping()
{
	ActionState = EActionState::EAS_Unoccupied;
}

void ASlashCharacter::Jump()
{
	Super::Jump();
}



// Called to bind functionality to input
void ASlashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MovementAction,ETriggerEvent::Triggered,this,&ASlashCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction,ETriggerEvent::Triggered,this,&ASlashCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction,ETriggerEvent::Started,this,&ASlashCharacter::Jump);
		EnhancedInputComponent->BindAction(EquipAction,ETriggerEvent::Started,this,&ASlashCharacter::Equip);
		EnhancedInputComponent->BindAction(AttackAction,ETriggerEvent::Started,this,&ASlashCharacter::Attack);
	}
	
}

