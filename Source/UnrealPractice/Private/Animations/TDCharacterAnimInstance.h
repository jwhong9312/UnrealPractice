// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TDCharacterAnimInstance.generated.h"

class UCharacterMovementComponent;
class UAnimMontage;

struct FAnimNotifyEvent;

UCLASS()
class UTDCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	void PlayBasicAttackMontage();
	void IncreaseBasicAttackMontageIndex(bool bIsComboAttack);

private:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UCharacterMovementComponent* GetCharacterMovementComponent(APawn* OwnerPawn) const;

	void SetSpeed(float VelocitySize);
	void SetIsAccelerating(float AccelerationSize);
	void SetIsInAir(bool bInIsInAir);
	void SetVerticalVelocity(float InVerticalVelocity);
	void SetCurrentBasicAttackMontageIndex(int32 NextIndex);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool bIsAccelerating;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool bIsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float VerticalVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TArray<TObjectPtr<UAnimMontage>> BasicAttackMontages;

	int CurrentBasicAttackMontageIndex = 0;
};
