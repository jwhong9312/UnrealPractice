// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/TDPlayerController.h"

#include "Widgets/TDPlayerWidget.h"
#include "Widgets/TDPlayerWidgetViewModel.h"
#include "Components/Character/TDCombatStatsComponent.h"

#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

void ATDPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (DefaultMappingContext)
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ATDPlayerController::BeginPlay()
{
	Super::BeginPlay();

	CreatePlayerWidget();
	InjectPlayerWidgetViewModelToCombatComponents();
}

void ATDPlayerController::CreatePlayerWidget()
{
	if (PlayerWidgetClass)
	{
		PlayerWidgetViewModel = NewObject<UTDPlayerWidgetViewModel>(this);

		PlayerWidget = CreateWidget<UTDPlayerWidget>(this, PlayerWidgetClass);
		
		PlayerWidget->SetViewModel(PlayerWidgetViewModel);
		PlayerWidget->AddToViewport();
	}
}

void ATDPlayerController::InjectPlayerWidgetViewModelToCombatComponents()
{
	const TArray<UTDCombatStatsComponent*> CombatStatsComponents = GetPlayerCombatStatsComponents();
	for (UTDCombatStatsComponent* CombatStatsComponent : CombatStatsComponents)
	{
		if (CombatStatsComponent)
		{
			CombatStatsComponent->SetViewModel(PlayerWidgetViewModel);
		}
	}
}

const TArray<UTDCombatStatsComponent*> ATDPlayerController::GetPlayerCombatStatsComponents() const
{
	TArray<UTDCombatStatsComponent*> CombatStatsComponents;

	UWorld* World = GetWorld();
	if (World)
	{
		TArray<AActor*> FoundCharacters;
		UGameplayStatics::GetAllActorsOfClass(World, ACharacter::StaticClass(), FoundCharacters);
		
		for (AActor* FoundCharacter : FoundCharacters)
		{
			if (UTDCombatStatsComponent* CombatStats = FoundCharacter->FindComponentByClass<UTDCombatStatsComponent>())
			{
				CombatStatsComponents.Add(CombatStats);
			}
		}
	}

	return CombatStatsComponents;
}
