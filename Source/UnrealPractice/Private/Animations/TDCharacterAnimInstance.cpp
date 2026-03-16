// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/TDCharacterAnimInstance.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UTDCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* OwnerPawn = TryGetPawnOwner();
	SetSpeed(OwnerPawn);
	SetIsAccelerating(OwnerPawn);
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
	ACharacter* OwnerCharacter = Cast<ACharacter>(OwnerPawn);
	if (OwnerCharacter)
	{
		UCharacterMovementComponent* CharacterMovementComponent = OwnerCharacter->GetCharacterMovement();
		if (CharacterMovementComponent)
		{
			bIsAccelerating = CharacterMovementComponent->GetCurrentAcceleration().Size() > 0.f;
		}
	}
}
