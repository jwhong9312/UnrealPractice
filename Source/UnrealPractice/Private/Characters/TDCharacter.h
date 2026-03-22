// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TDCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UCapsuleComponent;
class UInputAction;

struct FInputActionValue;

UCLASS()
class ATDCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	void BeginAttackHitDetection();
	void UpdateAttackHitDetection();
	void EndAttackHitDetection();

private:
	ATDCharacter();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void HandleMouseLookAction(const FInputActionValue& Value);
	void Look(float Yaw, float Pitch);

	void HandleMoveAction(const FInputActionValue& Value);
	void Move(float Right, float Forward);

	void HandleJumpAction(const FInputActionValue& Value);

	void HandleAttackAction(const FInputActionValue& Value);

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> MouseLookAction;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> AttackAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> SwordCollision;

	UPROPERTY()
	TSet<TObjectPtr<AActor>> DamagedActors;
};
