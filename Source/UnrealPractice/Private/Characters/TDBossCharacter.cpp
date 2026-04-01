// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/TDBossCharacter.h"

#include "Components/Character/TDCombatStatsComponent.h"

void ATDBossCharacter::TakeAttackDamage(float AttackDamage)
{
	if (CombatStatsComponent)
	{
		CombatStatsComponent->CalculateLeftHPBy(AttackDamage);
	}
}

void ATDBossCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	CombatStatsComponent = GetComponentByClass<UTDCombatStatsComponent>();
	if (CombatStatsComponent)
	{
		CombatStatsComponent->InitializeCombatStats(CharacterDataID);
	}
}
