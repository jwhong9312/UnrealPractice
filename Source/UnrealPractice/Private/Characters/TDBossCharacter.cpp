// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/TDBossCharacter.h"

#include "Components/Character/TDCombatStatsComponent.h"

void ATDBossCharacter::BeginPlay()
{
	Super::BeginPlay();

	CombatStatsComponent = GetComponentByClass<UTDCombatStatsComponent>();
	if (CombatStatsComponent)
	{
		CombatStatsComponent->InitializeCombatStats(CharacterDataID);
	}
}
