// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/TDBasicAttackAnimNotify.h"

#include "Animations/TDCharacterAnimInstance.h"

void UTDBasicAttackAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp)
	{
		UAnimInstance* AnimInstance = MeshComp->GetAnimInstance();
		if (AnimInstance)
		{
			UTDCharacterAnimInstance* TDAnimInstance = Cast<UTDCharacterAnimInstance>(AnimInstance);
			if (TDAnimInstance)
			{

			}
		}
	}
}
