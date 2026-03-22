// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/TDBossAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

ATDBossAIController::ATDBossAIController()
{
	BlackBoardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComponent"));
}

void ATDBossAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BehaviourTreeAsset)
	{
		UBlackboardData* BlackboardData = BehaviourTreeAsset->BlackboardAsset;
		UBlackboardComponent* BlackboardComp = BlackBoardComponent.Get();
		if (BlackboardData && BlackboardComp)
		{
			UseBlackboard(BlackboardData, BlackboardComp);

			RunBehaviorTree(BehaviourTreeAsset);
		}
	}
}
