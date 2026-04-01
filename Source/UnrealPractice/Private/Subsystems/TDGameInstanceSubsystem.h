// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TDGameInstanceSubsystem.generated.h"

class UDataTable;

struct FTDCharacterData;

UCLASS(config=Game)
class UTDGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	const FTDCharacterData* GetCharacterData(FName CharacterDataID) const;

private:
	void LoadCharacterDataTable();

private:
	UPROPERTY(config)
	TSoftObjectPtr<UDataTable> CharacterDataTableAsset;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UDataTable> CharacterDataTable;
};
