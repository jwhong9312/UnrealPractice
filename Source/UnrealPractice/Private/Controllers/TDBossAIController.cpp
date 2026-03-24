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

			if (RunBehaviorTree(BehaviorTree))
			{
				UE_LOG(LogTemp, Log, TEXT("Run Behavior Tree Succeed"));
			}
		}
	}
}

void ATDBossAIController::BeginPlay()
{
	Super::BeginPlay();

	FindTarget();
}

void ATDBossAIController::FindTarget()
{
	UWorld* World = GetWorld();
	if (World)
	{
		ATDCharacter* PlayerCharacter = Cast<ATDCharacter>(UGameplayStatics::GetActorOfClass(World, ATDCharacter::StaticClass()));
		if (PlayerCharacter && BlackBoardComponent)
		{
			BlackBoardComponent->SetValueAsObject(TargetActorKeyName, PlayerCharacter);
		}
	}
}
