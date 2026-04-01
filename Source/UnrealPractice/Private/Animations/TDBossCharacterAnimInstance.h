// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TDBossCharacterAnimInstance.generated.h"

UCLASS()
class UTDBossCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void PlayIdleAnim();

	UFUNCTION(BlueprintCallable)
	void PlayWalkAnim();

private:
	void SetIsWalking(bool bNewIsWalking);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	bool bIsWalking;
};
