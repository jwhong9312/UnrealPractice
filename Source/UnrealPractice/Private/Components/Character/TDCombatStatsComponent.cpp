// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Character/TDCombatStatsComponent.h"

#include "Subsystems/TDGameInstanceSubsystem.h"
#include "Data/TDCharacterData.h"

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
					DefaultHealthPoint = CharacterData->HealthPoint;
					DefaultMovementSpeed = CharacterData->MovementSpeed;
					AttackDamage = CharacterData->AttackDamage;

					UE_LOG(LogTemp, Log, TEXT("Combat stats initialized for %s: HP=%f, Speed=%f, AttackDamage=%f"), *CharacterDataID.ToString(), DefaultHealthPoint, DefaultMovementSpeed, AttackDamage);
				}
			}
		}
	}
}
