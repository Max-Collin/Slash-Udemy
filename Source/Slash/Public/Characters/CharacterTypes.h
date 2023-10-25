#pragma once

UENUM(BlueprintType)
enum class ECharacterState: uint8
{
	ESC_Unequipped UMETA(DisplayName ="Unequipped"),
	ESC_EquippedOneHandedWeapon UMETA(DisplayName ="Equipped One-Handed Weapon"),
	ESC_EquippedTwoHandedWeapon UMETA(DisplayName ="Equipped Two-Handed Weapon")
};
UENUM(BlueprintType)
enum class EActionState: uint8
{
	EAS_Unoccupied UMETA(DisplayName ="Unoccupied"),
	EAS_Attacking UMETA(DisplayName ="Attacking"),
	EAS_EquippingWeapon UMETA(DislayName = "EquippingWeapon")
	
};