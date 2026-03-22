// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TDBossAIController.generated.h"

class UBehaviorTree;
class UBlackboardComponent;

UCLASS()
class ATDBossAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ATDBossAIController();

private:
	virtual void OnPossess(APawn* InPawn) override;

private:
    // 에디터에서 할당할 비헤이비어 트리 애셋
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBehaviorTree> BehaviourTreeAsset;

    // 데이터 저장소인 블랙보드 컴포넌트
    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UBlackboardComponent> BlackBoardComponent;
};
