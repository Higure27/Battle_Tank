// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* possesedTank = GetControlledTank();
	if (possesedTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is the Player possesed tank"), *(possesedTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Player possesed tank was NOT FOUND"));
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

