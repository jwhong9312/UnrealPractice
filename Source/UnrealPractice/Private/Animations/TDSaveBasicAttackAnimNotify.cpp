// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/TDSaveBasicAttackAnimNotify.h"

#include "Animations/TDCharacterAnimInstance.h"
#include "Characters/TDCharacter.h"

void UTDSaveBasicAttackAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp)
	{
		UAnimInstance* AnimInstance = MeshComp->GetAnimInstance();
		if (AnimInstance)
		{
			UTDCharacterAnimInstance* TDAnimInstance = Cast<UTDCharacterAnimInstance>(AnimInstance);
			if (TDAnimInstance)
			{
				TDAnimInstance->SetNextAttackAllowed();
			}
		}
	}
}

void UTDBasicAttackComboTimeOverAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp)
	{
		UAnimInstance* AnimInstance = MeshComp->GetAnimInstance();
		if (AnimInstance)
		{
			UTDCharacterAnimInstance* TDAnimInstance = Cast<UTDCharacterAnimInstance>(AnimInstance);
			if (TDAnimInstance)
			{
				TDAnimInstance->SetComboTimeOver();
			}
		}
	}
}

// void UTDBasicAttackCollisionDetectionAnimNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
// {
// 
// }
// 
// void UTDBasicAttackCollisionDetectionAnimNotify::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference, float FrameDeltaTime)
// {
// 
// }
// 
// void UTDBasicAttackCollisionDetectionAnimNotify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
// {
// 
// }

void UTDBasicAttackCollisionDetectionAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp)
	{
		ATDCharacter* Character = Cast<ATDCharacter>(MeshComp->GetOwner());
		if (Character)
		{
			Character->CheckHitsByAttack();
		}
	}
}
