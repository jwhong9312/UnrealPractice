// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDCombatStatsComponent.generated.h"

class UTDPlayerWidgetViewModel;

enum class ETDCharacterRole : uint8;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UTDCombatStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void InitializeCombatStats(FName CharacterDataID);
	void SetViewModel(UTDPlayerWidgetViewModel* InViewModel);
	float GetAttackDamage() const { return AttackDamage; }
	void CalculateLeftHPBy(float EnemyAttackDamage);

private:
	void SetHealthPoint(float CurrentHP, float MaxHp);
	void SetMovementSpeed(float NewSpeed);

private:
	ETDCharacterRole CharacterRole;
	float DefaultMaxHealthPoint;
	float CurrentHealthPoint;
	float DefaultMovementSpeed;
	float AttackDamage;

	UPROPERTY()
	TObjectPtr<UTDPlayerWidgetViewModel> PlayerWidgetViewModel;
};
