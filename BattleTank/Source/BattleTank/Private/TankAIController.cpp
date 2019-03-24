// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ATank* possesedTank = GetControlledTank();
	if (possesedTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is the AI possesed tank"), *(possesedTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AI Possesed tank was NOT FOUND"));
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


