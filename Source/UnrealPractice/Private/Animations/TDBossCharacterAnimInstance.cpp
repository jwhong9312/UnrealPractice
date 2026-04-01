// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/TDBossCharacterAnimInstance.h"

void UTDBossCharacterAnimInstance::PlayIdleAnim()
{
	SetIsWalking(false);
}

void UTDBossCharacterAnimInstance::PlayWalkAnim()
{
	SetIsWalking(true);
}

void UTDBossCharacterAnimInstance::SetIsWalking(bool bNewIsWalking)
{
	bIsWalking = bNewIsWalking;
}
