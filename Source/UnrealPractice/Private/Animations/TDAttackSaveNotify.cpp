// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/TDAttackSaveNotify.h"

#include "Animations/TDCharacterAnimInstance.h"
#include "Characters/TDCharacter.h"
#include "Characters/TDBossCharacter.h"

UTDCharacterAnimInstance* GetCharacterAnimInstance(USkeletalMeshComponent* MeshComp)
{
	UTDCharacterAnimInstance* CharacterAnimInstance = nullptr;

	if (MeshComp)
	{
		UAnimInstance* AnimInstance = MeshComp->GetAnimInstance();
		if (AnimInstance)
		{
			CharacterAnimInstance = Cast<UTDCharacterAnimInstance>(AnimInstance);
		}
	}

	return CharacterAnimInstance;
}

ATDCharacter* GetCharacter(USkeletalMeshComponent* MeshComp)
{
	ATDCharacter* Character = nullptr;

	if (MeshComp)
	{
		APawn* Pawn = MeshComp->GetOwner<APawn>();
		if (Pawn)
		{
			Character = Cast<ATDCharacter>(Pawn);
		}
	}

	return Character;
}

ATDBossCharacter* GetBossCharacter(USkeletalMeshComponent* MeshComp)
{
	ATDBossCharacter* BossCharacter = nullptr;

	if (MeshComp)
	{
		APawn* Pawn = MeshComp->GetOwner<APawn>();
		if (Pawn)
		{
			BossCharacter = Cast<ATDBossCharacter>(Pawn);
		}
	}

	return BossCharacter;
}

void UTDAttackSaveNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	UTDCharacterAnimInstance* TDAnimInstance = GetCharacterAnimInstance(MeshComp);
	if (TDAnimInstance)
	{
		TDAnimInstance->SetNextAttackAllowed();
	}
}

void UTDComboOverNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	UTDCharacterAnimInstance* TDAnimInstance = GetCharacterAnimInstance(MeshComp);
	if (TDAnimInstance)
	{
		TDAnimInstance->SetComboTimeOver();
	}
}

void UTDCollisionState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	ATDCharacter* OwningCharacter = GetCharacter(MeshComp);
	if (OwningCharacter)
	{
		OwningCharacter->BeginAttackHitDetection();
	}

	ATDBossCharacter* BossCharacter = GetBossCharacter(MeshComp);
	if (BossCharacter)
	{
		BossCharacter->BeginAttackHitDetection();
	}
}

void UTDCollisionState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	ATDCharacter* OwningCharacter = GetCharacter(MeshComp);
	if (OwningCharacter)
	{
		OwningCharacter->UpdateAttackHitDetection();
	}

	ATDBossCharacter* BossCharacter = GetBossCharacter(MeshComp);
	if (BossCharacter)
	{
		BossCharacter->UpdateAttackHitDetection();
	}
}

void UTDCollisionState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	ATDCharacter* OwningCharacter = GetCharacter(MeshComp);
	if (OwningCharacter)
	{
		OwningCharacter->EndAttackHitDetection();
	}

	ATDBossCharacter* BossCharacter = GetBossCharacter(MeshComp);
	if (BossCharacter)
	{
		BossCharacter->EndAttackHitDetection();
	}
}
