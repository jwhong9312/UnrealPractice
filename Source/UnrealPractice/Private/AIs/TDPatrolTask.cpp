// Fill out your copyright notice in the Description page of Project Settings.


#include "AIs/TDPatrolTask.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UTDPatrolTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FTDPatrolTaskMemory* Memory = (FTDPatrolTaskMemory*)NodeMemory;
	Memory->bRequestedMove = false;

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComponent)
	{
		return EBTNodeResult::Failed;
	}

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	APawn* Pawn = AIController->GetPawn();
	if (!Pawn)
	{
		return EBTNodeResult::Failed;
	}

	UWorld* World = Pawn->GetWorld();
	if (!World)
	{
		return EBTNodeResult::Failed;
	}

	// Find random navigable point within PatrolRadius
	FVector Origin = Pawn->GetActorLocation();
	FNavLocation RandomNavLocation;
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(World);
	bool bFoundLocation = NavSystem->GetRandomPointInNavigableRadius(Origin, PatrolRadius, RandomNavLocation);
	if (!bFoundLocation)
	{
		return EBTNodeResult::Failed;
	}

	// Write chosen location to blackboard (Vector)
	BlackboardComponent->SetValueAsVector(PatrolLocationKey.SelectedKeyName, RandomNavLocation.Location);

	// Request move
	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalLocation(RandomNavLocation.Location);
	MoveRequest.SetAcceptanceRadius(AcceptanceRadius);
	MoveRequest.SetUsePathfinding(true);

	// Use controller MoveToLocation (starts async path following)
	FPathFollowingRequestResult MoveResult = AIController->MoveTo(MoveRequest);

	// store memory for TickTask to check progress
	Memory->bRequestedMove = true;
	Memory->AcceptanceRadius = AcceptanceRadius;
	Memory->TargetLocation = RandomNavLocation.Location;

	return EBTNodeResult::InProgress;
}
