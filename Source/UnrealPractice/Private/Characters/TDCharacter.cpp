// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/TDCharacter.h"

#include "Animations/TDCharacterAnimInstance.h"

#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ATDCharacter::ATDCharacter()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 800.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void ATDCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
		if (MouseLookAction)
		{
			EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ATDCharacter::HandleMouseLookAction);
		}

		if (MoveAction)
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATDCharacter::HandleMoveAction);
		}

		if (JumpAction)
		{
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ATDCharacter::HandleJumpAction);
		}

		if (AttackAction)
		{
			EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ATDCharacter::HandleAttackAction);
		}
	}
}

void ATDCharacter::HandleMouseLookAction(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	Look(LookAxisVector.X, LookAxisVector.Y);
}

void ATDCharacter::Look(float Yaw, float Pitch)
{
	AddControllerYawInput(Yaw);
	AddControllerPitchInput(Pitch);
}

void ATDCharacter::HandleMoveAction(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	Move(MovementVector.X, MovementVector.Y);
}

void ATDCharacter::Move(float Right, float Forward)
{
	AController* CurrentController = GetController();
	if (CurrentController)
	{
		// find out which way is forward
		const FRotator Rotation = CurrentController->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void ATDCharacter::HandleJumpAction(const FInputActionValue& Value)
{
	bool bNeedToJump = Value.Get<bool>();

	if (bNeedToJump)
	{
		Jump();
	}
}

void ATDCharacter::HandleAttackAction(const FInputActionValue& Value)
{
	bool bNeedToAttack = Value.Get<bool>();
	
	if (bNeedToAttack)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance)
		{
			UTDCharacterAnimInstance* TDAnimInstance = Cast<UTDCharacterAnimInstance>(AnimInstance);
			if (TDAnimInstance)
			{
				TDAnimInstance->PlayBasicAttackMontage();
			}
		}
	}
}
