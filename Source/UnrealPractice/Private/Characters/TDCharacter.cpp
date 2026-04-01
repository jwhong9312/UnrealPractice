// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/TDCharacter.h"

#include "Animations/TDCharacterAnimInstance.h"
#include "Components/Character/TDCombatStatsComponent.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void ATDCharacter::BeginAttackHitDetection()
{
	DamagedActors.Empty();

	if (SwordCollision)
	{
		SwordCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
}

void ATDCharacter::UpdateAttackHitDetection()
{
	TArray<AActor*> CollidingActors;
	if (SwordCollision)
	{
		SwordCollision->GetOverlappingActors(CollidingActors);

		for (AActor* Actor : CollidingActors)
		{
			if (!Actor) continue;

			if (Actor != this && !DamagedActors.Contains(Actor))
			{
				UE_LOG(LogTemp, Log, TEXT("%s Actor was hit"), *Actor->GetActorLabel());
				DamagedActors.Add(Actor);
			}
		}
	}
}

void ATDCharacter::EndAttackHitDetection()
{
	if (SwordCollision)
	{
		SwordCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

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
	// 보스 캐릭터에서 카메라와 충돌 option 꺼야 함
	CameraBoom->ProbeChannel = ECC_Camera;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	USkeletalMeshComponent* SkeletalMesh = GetMesh();
	if (SkeletalMesh)
	{
		SwordCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("SwordCollision"));
		SwordCollision->SetupAttachment(SkeletalMesh, TEXT("hand_rSocket"));
		SwordCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		SwordCollision->SetCapsuleHalfHeight(65.f);
		SwordCollision->SetCapsuleRadius(6.f);
		SwordCollision->SetRelativeLocation(FVector(0.f, 0.f, SwordCollision->GetUnscaledCapsuleHalfHeight() * 0.5f));
	}
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
			EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &ATDCharacter::HandleAttackAction);
		}
	}
}

void ATDCharacter::BeginPlay()
{
	Super::BeginPlay();

	CombatStatsComponent = GetComponentByClass<UTDCombatStatsComponent>();
	if (CombatStatsComponent)
	{
		CombatStatsComponent->InitializeCombatStats(CharacterDataID);
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