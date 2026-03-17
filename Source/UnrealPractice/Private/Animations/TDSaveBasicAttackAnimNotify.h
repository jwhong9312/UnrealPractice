// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "TDSaveBasicAttackAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class UTDSaveBasicAttackAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

private:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
};

UCLASS()
class UTDBasicAttackComboTimeOverAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

private:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
};

// UCLASS()
// class UTDBasicAttackCollisionDetectionAnimNotify : public UAnimNotifyState
// {
// 	GENERATED_BODY()
// 
// private:
// 	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
// 	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference, float FrameDeltaTime) override;
// 	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
// 
// };

UCLASS()
class UTDBasicAttackCollisionDetectionAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

private:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};