// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Character/TDCombatStatsComponent.h"

#include "Widgets/TDPlayerWidgetViewModel.h"

#include "Subsystems/TDGameInstanceSubsystem.h"
#include "Data/TDCharacterData.h"
#include "GameFramework/CharacterMovementComponent.h"

void UTDCombatStatsComponent::InitializeCombatStats(FName CharacterDataID)
{
	UWorld* World = GetWorld();
	if (World)
	{
		UGameInstance* GameInstance = World->GetGameInstance();
		if (GameInstance)
		{
			UTDGameInstanceSubsystem* GameInstanceSubsystem = GameInstance->GetSubsystem<UTDGameInstanceSubsystem>();
			if (GameInstanceSubsystem)
			{
				const FTDCharacterData* CharacterData = GameInstanceSubsystem->GetCharacterData(CharacterDataID);
				if (CharacterData)
				{
					CharacterRole = CharacterData->CharacterRole;
					DefaultMaxHealthPoint = CharacterData->MaxHealthPoint;
					CurrentHealthPoint = DefaultMaxHealthPoint;
					DefaultMovementSpeed = CharacterData->MovementSpeed;
					AttackDamage = CharacterData->AttackDamage;
				}
			}
		}
	}
}

void UTDCombatStatsComponent::SetViewModel(UTDPlayerWidgetViewModel* InViewModel)
{
	PlayerWidgetViewModel = InViewModel;

	SetHealthPoint(CurrentHealthPoint, DefaultMaxHealthPoint);
	SetMovementSpeed(DefaultMovementSpeed);
}

void UTDCombatStatsComponent::CalculateLeftHPBy(float EnemyAttackDamage)
{
	CurrentHealthPoint -= EnemyAttackDamage;
	CurrentHealthPoint = FMath::Clamp(CurrentHealthPoint, 0.0f, DefaultMaxHealthPoint);

	SetHealthPoint(CurrentHealthPoint, DefaultMaxHealthPoint);
}

void UTDCombatStatsComponent::SetHealthPoint(float CurrentHP, float MaxHp)
{
	if (PlayerWidgetViewModel)
	{
		if (CharacterRole == ETDCharacterRole::Warrior)
		{
			PlayerWidgetViewModel->UpdatePlayerHealthPercent(CurrentHealthPoint, DefaultMaxHealthPoint);
		}
		else if (CharacterRole == ETDCharacterRole::Boss)
		{
			PlayerWidgetViewModel->UpdateBossHealthPercent(CurrentHealthPoint, DefaultMaxHealthPoint);
		}
	}
}

void UTDCombatStatsComponent::SetMovementSpeed(float NewSpeed)
{
	AActor* OwnerActor = GetOwner();
	if (OwnerActor)
	{
		UCharacterMovementComponent* MovementComponent = OwnerActor->GetComponentByClass<UCharacterMovementComponent>();
		if (MovementComponent)
		{
			MovementComponent->MaxWalkSpeed = NewSpeed;
		}
	}
}
