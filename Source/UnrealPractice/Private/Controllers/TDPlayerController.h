// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TDPlayerController.generated.h"

class UInputMappingContext;
class UTDCombatStatsComponent;
class UTDPlayerWidget;
class UTDPlayerWidgetViewModel;

UCLASS(config=Game)
class ATDPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

private:
	void CreatePlayerWidget();
	void InjectPlayerWidgetViewModelToCombatComponents();
	const TArray<UTDCombatStatsComponent*> GetPlayerCombatStatsComponents() const;
	
private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(config)
	TSubclassOf<UTDPlayerWidget> PlayerWidgetClass;

	UPROPERTY()
	TObjectPtr<UTDPlayerWidget> PlayerWidget;

	UPROPERTY()
	TObjectPtr<UTDPlayerWidgetViewModel> PlayerWidgetViewModel;
};
