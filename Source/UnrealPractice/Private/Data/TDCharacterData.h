// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TDCharacterData.generated.h"

UENUM(BlueprintType)
enum class ETDCharacterRole : uint8
{
	Warrior UMETA(DisplayName = "Warrior"),
	Boss UMETA(DisplayName = "Boss")
};

USTRUCT(BlueprintType)
struct FTDCharacterData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ETDCharacterRole CharacterRole;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHealthPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AttackDamage;
};