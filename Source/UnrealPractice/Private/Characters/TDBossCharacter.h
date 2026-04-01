// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TDBossCharacter.generated.h"

class UTDCombatStatsComponent;

UCLASS()
class ATDBossCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	void TakeAttackDamage(float AttackDamage);

private:
	virtual void PostInitializeComponents() override;

private:
	UPROPERTY(config)
	FName CharacterDataID;

	UPROPERTY()
	TObjectPtr<UTDCombatStatsComponent> CombatStatsComponent;
};
