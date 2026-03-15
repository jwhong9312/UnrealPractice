// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TDCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

UCLASS()
class ATDCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	ATDCharacter();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void HandleMouseLookAction(const FInputActionValue& Value);
	void Look(float Yaw, float Pitch);

	void HandleMoveAction(const FInputActionValue& Value);
	void Move(float Right, float Forward);

private:
	UPROPERTY(EditAnywhere)
	UInputAction* MouseLookAction;

	UPROPERTY(EditAnywhere)
	UInputAction* MoveAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

};
