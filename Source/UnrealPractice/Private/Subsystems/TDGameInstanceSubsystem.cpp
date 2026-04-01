// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/TDGameInstanceSubsystem.h"

#include "Data/TDCharacterData.h"

void UTDGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	LoadCharacterDataTable();
}

const FTDCharacterData* UTDGameInstanceSubsystem::GetCharacterData(FName CharacterDataID) const
{
	if (!CharacterDataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("CharacterDataTable is not loaded."));
		return nullptr;
	}

	return CharacterDataTable->FindRow<FTDCharacterData>(CharacterDataID, TEXT("Character Data"));
}

void UTDGameInstanceSubsystem::LoadCharacterDataTable()
{
	CharacterDataTable = CharacterDataTableAsset.LoadSynchronous();
}
