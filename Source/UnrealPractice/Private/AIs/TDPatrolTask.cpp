// Fill out your copyright notice in the Description page of Project Settings.


#include "AIs/TDPatrolTask.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UTDPatrolTask::UTDPatrolTask()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UTDPatrolTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

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

void UTDPatrolTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	FTDPatrolTaskMemory* Memory = (FTDPatrolTaskMemory*)NodeMemory;
	if (!Memory->bRequestedMove)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	APawn* Pawn = AIController->GetPawn();
	if (!Pawn)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	FVector CurrentLocation = Pawn->GetActorLocation();
	float DistSquared2D = FVector::DistSquared2D(CurrentLocation, Memory->TargetLocation);
	float AcceptSquared = FMath::Square(Memory->AcceptanceRadius);

	// Arrived
	if (DistSquared2D <= AcceptSquared)
	{
		// Stop movement and finish node
		AIController->StopMovement();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
	else if(AIController->GetMoveStatus() == EPathFollowingStatus::Idle)
	{
		// If we are not moving and haven't arrived, something went wrong
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
}

EBTNodeResult::Type UTDPatrolTask::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	// Ensure any ongoing movement is stopped
	if (AAIController* AIController = OwnerComp.GetAIOwner())
	{
		AIController->StopMovement();
	}

	return EBTNodeResult::Aborted;
}
