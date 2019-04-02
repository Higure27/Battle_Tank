// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "GameFramework/Actor.h"
#include "Tank.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	//Get pointer to this tank
	possesedTank = Cast<ATank>(GetPawn());
	if (possesedTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is the AI possesed tank"), *(possesedTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AI Possesed tank was NOT FOUND"));
	}
	//Find player's tank
	targetTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
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

	if (targetTank)
	{
		MoveToActor(targetTank, acceptanceRadius);
		possesedTank->AimAt(targetTank->GetActorLocation());
		possesedTank->Fire();
	}
	else
	{
		targetTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	}


}

