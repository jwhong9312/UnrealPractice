// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/TDBossAIController.h"

#include "Characters/TDCharacter.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionTypes.h"

ATDBossAIController::ATDBossAIController()
{
	BlackBoardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComponent"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
}

void ATDBossAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	BossBehaviorTree = BossBehaviorTreeAsset.LoadSynchronous();
	if (BossBehaviorTree)
	{
		UBlackboardData* BlackboardData = BossBehaviorTree->BlackboardAsset;
		UBlackboardComponent* BlackboardComp = BlackBoardComponent.Get();
		UBehaviorTree* BehaviorTree = BossBehaviorTree.Get();
		if (BlackboardData && BlackboardComp && BehaviorTree)
		{
			UseBlackboard(BlackboardData, BlackboardComp);

			RunBehaviorTree(BehaviorTree);
		}
	}
}

void ATDBossAIController::BeginPlay()
{
	InitializePerceptionComponent();
}

void ATDBossAIController::InitializePerceptionComponent()
{
	if (!PerceptionComponent || !SightConfig)
	{
		UE_LOG(LogTemp, Warning, TEXT("PerceptionComponent is not valid"));
		return;
	}

	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	PerceptionComponent->ConfigureSense(*SightConfig);
	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ATDBossAIController::HandleTargetPerceptionUpdated);
}

void ATDBossAIController::HandleTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Actor && BlackBoardComponent)
	{
		UE_LOG(LogTemp, Log, TEXT("Target detected: %s"), *Actor->GetActorLabel());
		bool bIsSensed = Stimulus.WasSuccessfullySensed();
		UE_LOG(LogTemp, Log, TEXT("Target %s"), bIsSensed ? TEXT("sensed") : TEXT("lost"));
		BlackBoardComponent->SetValueAsBool(LineOfSightKeyName, bIsSensed);
		BlackBoardComponent->SetValueAsObject(TargetKeyName, Actor);
	}
}
