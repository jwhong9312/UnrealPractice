// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/TDCharacterAnimInstance.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UTDCharacterAnimInstance::PlayBasicAttackMontage()
{
	UE_LOG(LogTemp, Warning, TEXT("PlayBasicAttackMontage called. Current index: %d"), CurrentBasicAttackMontageIndex);
	Montage_Play(BasicAttackMontages[CurrentBasicAttackMontageIndex]);
	IncreaseBasicAttackMontageIndex(true);
}

void UTDCharacterAnimInstance::IncreaseBasicAttackMontageIndex(bool bIsComboAttack)
{
	int32 NextIndex = (CurrentBasicAttackMontageIndex + 1) % BasicAttackMontages.Num();

	SetCurrentBasicAttackMontageIndex(bIsComboAttack ? NextIndex : 0);
}

void UTDCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* OwnerPawn = TryGetPawnOwner();
	if (OwnerPawn)
	{
		UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovementComponent(OwnerPawn);
		if (CharacterMovementComponent)
		{
			SetSpeed(CharacterMovementComponent->Velocity.Size());
			SetIsAccelerating(CharacterMovementComponent->GetCurrentAcceleration().Size());
			SetIsInAir(CharacterMovementComponent->IsFalling());
			SetVerticalVelocity(CharacterMovementComponent->Velocity.Z);
		}
	}
}

UCharacterMovementComponent* UTDCharacterAnimInstance::GetCharacterMovementComponent(APawn* OwnerPawn) const
{
	UCharacterMovementComponent* CharacterMovementComponent = nullptr;

	ACharacter* OwnerCharacter = Cast<ACharacter>(OwnerPawn);
	if (OwnerCharacter)
	{
		CharacterMovementComponent = OwnerCharacter->GetCharacterMovement();
	}

	return CharacterMovementComponent;
}

void UTDCharacterAnimInstance::SetSpeed(float VelocitySize)
{
	Speed = VelocitySize;
}

void UTDCharacterAnimInstance::SetIsAccelerating(float AccelerationSize)
{
	bIsAccelerating = AccelerationSize > 0.f;
}

void UTDCharacterAnimInstance::SetIsInAir(bool bInIsInAir)
{
	bIsInAir = bInIsInAir;
}

void UTDCharacterAnimInstance::SetVerticalVelocity(float InVerticalVelocity)
{
	VerticalVelocity = InVerticalVelocity;
}

void UTDCharacterAnimInstance::SetCurrentBasicAttackMontageIndex(int32 NextIndex)
{
	CurrentBasicAttackMontageIndex = NextIndex;
}
