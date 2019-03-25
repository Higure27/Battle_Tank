// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	possesedTank = GetControlledTank();
	if (possesedTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is the AI possesed tank"), *(possesedTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AI Possesed tank was NOT FOUND"));
	}
	targetTank = GetPlayerTank();
	if (targetTank)
	{
		UE_LOG(LogTemp, Warning, TEXT(" AI Tank found %s is the player possesed tank"), *(targetTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Player Possesed tank was NOT FOUND"));
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	possesedTank->AimAt(targetTank->GetActorLocation());

}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	ATank * playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	return playerTank;
}

