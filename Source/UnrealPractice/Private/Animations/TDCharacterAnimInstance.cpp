// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/TDCharacterAnimInstance.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UTDCharacterAnimInstance::PlayBasicAttackMontage()
{
	if (BasicAttack1Montage)
	{
		Montage_Play(BasicAttack1Montage);
	}
}

void UTDCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* OwnerPawn = TryGetPawnOwner();
	SetSpeed(OwnerPawn);
	SetIsAccelerating(OwnerPawn);
	SetIsInAir(OwnerPawn);
	SetVerticalVelocity(OwnerPawn);
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

void UTDCharacterAnimInstance::SetSpeed(APawn* OwnerPawn)
{
	if (OwnerPawn)
	{
		Speed = OwnerPawn->GetVelocity().Size();
	}
}

void UTDCharacterAnimInstance::SetIsAccelerating(APawn* OwnerPawn)
{
	UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovementComponent(OwnerPawn);

	if (CharacterMovementComponent)
	{
		bIsAccelerating = CharacterMovementComponent->GetCurrentAcceleration().Size() > 0.f;
	}
}

void UTDCharacterAnimInstance::SetIsInAir(APawn* OwnerPawn)
{
	UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovementComponent(OwnerPawn);

	if (CharacterMovementComponent)
	{
		bIsInAir = CharacterMovementComponent->IsFalling();
	}
}

void UTDCharacterAnimInstance::SetVerticalVelocity(APawn* OwnerPawn)
{
	UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovementComponent(OwnerPawn);

	if (CharacterMovementComponent)
	{
		VerticalVelocity = CharacterMovementComponent->Velocity.Z;
	}
}
