// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/TDBasicAttackInputBlockAnimNotify.h"

#include "Animations/TDCharacterAnimInstance.h"

void UTDBasicAttackInputBlockAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
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
