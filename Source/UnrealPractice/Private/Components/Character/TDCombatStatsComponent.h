// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDCombatStatsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UTDCombatStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void InitializeCombatStats(FName CharacterDataID);

private:
	float DefaultHealthPoint;
	float DefaultMovementSpeed;
	float AttackDamage;
};
