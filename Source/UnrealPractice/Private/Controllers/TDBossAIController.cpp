// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/TDBossAIController.h"

#include "Characters/TDCharacter.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"

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

			RunBehaviorTree(BehaviorTree);
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