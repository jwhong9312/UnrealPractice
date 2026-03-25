// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TDPatrolTask.generated.h"

struct FTDPatrolTaskMemory
{
	FVector TargetLocation;
	float AcceptanceRadius;
	bool bRequestedMove;
};

UCLASS()
class UTDPatrolTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UTDPatrolTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual uint16 GetInstanceMemorySize() const override { return sizeof(FTDPatrolTaskMemory); }

private:
	UPROPERTY(EditAnywhere)
	float PatrolRadius = 1000.f;

	UPROPERTY(EditAnywhere)
	float AcceptanceRadius = 50.f;

	UPROPERTY(EditAnywhere)
	float PatrolSpeed = 170.f;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector PatrolLocationKey;
};
