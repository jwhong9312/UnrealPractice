// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/TDAttackSaveNotify.h"

#include "Animations/TDCharacterAnimInstance.h"
#include "Characters/TDCharacter.h"

void UTDAttackSaveNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
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

void UTDComboOverNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
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

void UTDCollisionBeginNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp)
	{
		ATDCharacter* Character = Cast<ATDCharacter>(MeshComp->GetOwner());
		if (Character)
		{
			Character->SetWeaponCollisionEnabled(true);
		}
	}
}