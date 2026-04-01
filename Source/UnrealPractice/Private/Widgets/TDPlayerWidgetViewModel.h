// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "TDPlayerWidgetViewModel.generated.h"

/**
 * 
 */
UCLASS()
class UTDPlayerWidgetViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	void UpdatePlayerHealthPercent(float CurrentHealth, float MaxHealth);
	void UpdateBossHealthPercent(float CurrentHealth, float MaxHealth);

private:
	void SetPlayerHealthPercent(float InHealthPercent);
	void SetBossHealthPercent(float InHealthPercent);
	
private:
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess = true))
	float PlayerHealthPercent;

	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess = true))
	float BossHealthPercent;
};
