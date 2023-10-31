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
UENUM(BlueprintType)
enum class EDeathPose:uint8
{
	EDP_Alive UMETA(DisplayName = "Alive"),
	EDP_Death1 UMETA(DisplayName = "Death1"),
	EDP_Death2 UMETA(DisplayName = "Death2"),
	EDP_Death3 UMETA(DisplayName = "Death3"),
	EDP_Death4 UMETA(DisplayName = "Death4"),
	EDP_Death5 UMETA(DisplayName = "Death5")
};

