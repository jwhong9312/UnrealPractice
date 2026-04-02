// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/TDBossCharacter.h"

#include "Components/Character/TDCombatStatsComponent.h"
#include "Characters/TDCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

void ATDBossCharacter::BeginAttackHitDetection()
{
	DamagedActors.Empty();

	if (FistCollision)
	{
		FistCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
}

void ATDBossCharacter::UpdateAttackHitDetection()
{
	TArray<AActor*> CollidingActors;
	if (FistCollision)
	{
		FistCollision->GetOverlappingActors(CollidingActors);

		for (AActor* Actor : CollidingActors)
		{
			if (!Actor) continue;

			if (Actor != this && !DamagedActors.Contains(Actor))
			{
				UE_LOG(LogTemp, Log, TEXT("%s Actor was hit"), *Actor->GetActorLabel());
				DamagedActors.Add(Actor);

				ATDCharacter* PlayerCharacter = Cast<ATDCharacter>(Actor);
				if (PlayerCharacter && CombatStatsComponent)
				{
					PlayerCharacter->TakeAttackDamage(CombatStatsComponent->GetAttackDamage());
				}
			}
		}
	}
}

void ATDBossCharacter::EndAttackHitDetection()
{
	if (FistCollision)
	{
		FistCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ATDBossCharacter::TakeAttackDamage(float AttackDamage)
{
	if (CombatStatsComponent)
	{
		CombatStatsComponent->CalculateLeftHPBy(AttackDamage);
	}
}

ATDBossCharacter::ATDBossCharacter()
{
	USkeletalMeshComponent* SkeletalMesh = GetMesh();
	if (SkeletalMesh)
	{
		FistCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("FistCollision"));
		FistCollision->SetupAttachment(SkeletalMesh, TEXT("Muzzle_01"));
		FistCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		FistCollision->SetCapsuleHalfHeight(100.f);
		FistCollision->SetCapsuleRadius(100.f);
	}
}

void ATDBossCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	CombatStatsComponent = GetComponentByClass<UTDCombatStatsComponent>();
	if (CombatStatsComponent)
	{
		CombatStatsComponent->InitializeCombatStats(CharacterDataID);

		CombatStatsComponent->GetOnCharacterDeath().AddUObject(this, &ATDBossCharacter::HandleBossCharacterDeath);
	}
}

void ATDBossCharacter::HandleBossCharacterDeath()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Warning, TEXT("World is null in HandleBossCharacterDeath"));
		return;
	}

	UGameplayStatics::OpenLevel(this, FName(*World->GetName()));
}
