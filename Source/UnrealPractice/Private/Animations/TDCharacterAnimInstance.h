// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TDCharacterAnimInstance.generated.h"

class UCharacterMovementComponent;

UCLASS()
class UTDCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
private:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UCharacterMovementComponent* GetCharacterMovementComponent(APawn* OwnerPawn) const;

	void SetSpeed(APawn* OwnerPawn);
	void SetIsAccelerating(APawn* OwnerPawn);
	void SetIsInAir(APawn* OwnerPawn);
	void SetVerticalVelocity(APawn* OwnerPawn);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool bIsAccelerating;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool bIsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float VerticalVelocity;
};
