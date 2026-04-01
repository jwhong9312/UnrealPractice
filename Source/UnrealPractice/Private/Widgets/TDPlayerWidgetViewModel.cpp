// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/TDPlayerWidgetViewModel.h"

void UTDPlayerWidgetViewModel::UpdatePlayerHealthPercent(float CurrentHealth, float MaxHealth)
{
	if (MaxHealth > 0.f)
	{
		float HealthPercent = CurrentHealth / MaxHealth;

		SetPlayerHealthPercent(HealthPercent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MaxHealth is zero or negative, cannot calculate health percent."));
		return;
	}
}

void UTDPlayerWidgetViewModel::UpdateBossHealthPercent(float CurrentHealth, float MaxHealth)
{
	if (MaxHealth > 0.f)
	{
		float HealthPercent = CurrentHealth / MaxHealth;

		SetBossHealthPercent(HealthPercent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MaxHealth is zero or negative, cannot calculate health percent."));
		return;
	}
}

void UTDPlayerWidgetViewModel::SetPlayerHealthPercent(float InHealthPercent)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(PlayerHealthPercent, InHealthPercent))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(PlayerHealthPercent);
	}
}

void UTDPlayerWidgetViewModel::SetBossHealthPercent(float InHealthPercent)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(BossHealthPercent, InHealthPercent))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(BossHealthPercent);
	}
}
