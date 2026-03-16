// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TDCharacterAnimInstance.generated.h"

UCLASS()
class UTDCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
private:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void SetSpeed(APawn* OwnerPawn);
	void SetIsAccelerating(APawn* OwnerPawn);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool bIsAccelerating;
};
