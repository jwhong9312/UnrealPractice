// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/TDBossCharacter.h"

#include "Components/Character/TDCombatStatsComponent.h"

#include "Components/CapsuleComponent.h"

void ATDBossCharacter::TakeAttackDamage(float AttackDamage)
{
	if (CombatStatsComponent)
	{
		CombatStatsComponent->CalculateLeftHPBy(AttackDamage);
	}
}

ATDBossCharacter::ATDBossCharacter()
{
	USkeletalMeshComponent* SkeletalMesh = GetMesh();
	if (SkeletalMesh)
	{
		FistCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("FistCollision"));
		FistCollision->SetupAttachment(SkeletalMesh, TEXT("FistCollisionCenter"));
		FistCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		FistCollision->SetCapsuleHalfHeight(30.f);
		FistCollision->SetCapsuleRadius(35.f);
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
