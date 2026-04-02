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
	void BeginAttackHitDetection();
	void UpdateAttackHitDetection();
	void EndAttackHitDetection();
	void TakeAttackDamage(float AttackDamage);

private:
	ATDBossCharacter();
	virtual void PostInitializeComponents() override;

	void HandleBossCharacterDeath();

private:
	UPROPERTY(config)
	FName CharacterDataID;

	UPROPERTY()
	TObjectPtr<UTDCombatStatsComponent> CombatStatsComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> FistCollision;

	UPROPERTY()
	TSet<TObjectPtr<AActor>> DamagedActors;
};
