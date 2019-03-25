// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"

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

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrossHair();

}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrossHair()
{
	if (!GetControlledTank()) { return; }

	FVector hitLocation;
	
	if (GetSightHitLocation(&hitLocation))
	{

		//Tell controlled tank to aim at that point
		GetControlledTank()->AimAt(hitLocation);
	}
	

}

//Get world location of linetrace through crosshair
//if it hits through the landscape return true
bool ATankPlayerController::GetSightHitLocation(FVector * outHitLocation) const
{
	//*outHitLocation = FVector(1.0f);
	//Find the crosshair position
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);

	FVector2D dotScreenLocation(viewportSizeX*crossHairXLocation, viewportSizeY*crossHairYLocation);
	 
	FVector lookDirection;
	if (GetLookDirection(dotScreenLocation, lookDirection))
	{
		
		if (GetLookVectorHitLocation(lookDirection, *outHitLocation)) { return true; }
	}
	
	return false;
	
}

//"De-project" the screen position of the cross-hair to a world direction
bool ATankPlayerController::GetLookDirection(FVector2D dotScreenLocation, FVector& lookDirection) const
{
	FVector cameraWorldLocation;//To be discarded
	return (DeprojectScreenPositionToWorld(dotScreenLocation.X, dotScreenLocation.Y, cameraWorldLocation, lookDirection));
}

//Line-trace along that look direction, and check what we hit (up to a max range)
bool ATankPlayerController::GetLookVectorHitLocation(FVector lookDirection, FVector& outHitLocation) const
{
	FHitResult lineTraceHit;
	FVector startVector = PlayerCameraManager->GetCameraLocation();
	FVector endVector = startVector + lookDirection * lineTraceRange;

	if (GetWorld()->LineTraceSingleByChannel(lineTraceHit, startVector, endVector, ECollisionChannel::ECC_Visibility))
	{
		outHitLocation = lineTraceHit.Location;
		return true;
	}

	outHitLocation = FVector(0.f);
	return false;
}