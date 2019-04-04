// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "GameFramework/Actor.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
//Depends on movement component through pathfinding (MoveToActor -> RequestDirectMove)

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	//Get pointer to this tank
	aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(aimingComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("AI Aiming component NOT FOUND"));
	}
	//Find player's tank
	targetTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!ensure(targetTank))
	{
		UE_LOG(LogTemp, Error, TEXT("Player Possesed tank was NOT FOUND"));
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!ensure(aimingComponent)) { return; }

	if (ensure(targetTank))
	{
		MoveToActor(targetTank, acceptanceRadius);
		aimingComponent->AimAt(targetTank->GetActorLocation());
		if (aimingComponent->GetFiringState() == EFIRINGSTATUS::LockedOn)
		{
			aimingComponent->Fire();
		}
	}
	else
	{
		targetTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	}


}

