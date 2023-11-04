﻿#pragma once

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
enum  EDeathPose
{
	
	EDP_Death1 UMETA(DisplayName = "Death1"),
	EDP_Death2 UMETA(DisplayName = "Death2"),
	EDP_Death3 UMETA(DisplayName = "Death3"),
	EDP_Death4 UMETA(DisplayName = "Death4"),
	EDP_Death5 UMETA(DisplayName = "Death5"),

	EDP_MAX  UMETA(DisplayName = "DefaultMAX")
};


UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	
	EES_Patrolling UMETA(DisplayName = "Patrolling"),
	EES_Chasing UMETA(DisplayName = "Chasing"),
	EES_Attacking UMETA(DisplayName = "Attacking"),
	EES_Engaged UMETA(DisplayName = "Engaged"),
	EES_Dead UMETA(DisplayName = "Dead")
};

