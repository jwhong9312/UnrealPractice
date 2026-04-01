// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TDBossCharacter.generated.h"

class UTDCombatStatsComponent;

UCLASS(config=Game)
class ATDBossCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<UTDCombatStatsComponent> CombatStatsComponent;

	UPROPERTY(config)
	FName CharacterDataID;
};
