// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float releativeSpeed)
{
	//UE_LOG(LogTemp, Warning, TEXT("%f elevation degrees per second"), releativeSpeed);

	releativeSpeed = FMath::Clamp(releativeSpeed, -1.f, 1.f);
	// Framerate Independent by using delta 
	float elevationChange = releativeSpeed * maxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float newElevation = RelativeRotation.Pitch + elevationChange;
	float clampedNewElevation = FMath::Clamp(newElevation, minElevationDegrees, maxElevationDegrees);
	UE_LOG(LogTemp, Warning, TEXT("Found aim solution, New elevation is %f "), clampedNewElevation);
	SetRelativeRotation(FRotator(clampedNewElevation,0,0));
}


