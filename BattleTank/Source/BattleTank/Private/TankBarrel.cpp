// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float relativeSpeed)
{
	relativeSpeed = FMath::Clamp(relativeSpeed, -1.f, 1.f);
	// Framerate Independent by using delta 
	float elevationChange = relativeSpeed * maxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float newElevation = GetRelativeRotation().Pitch + elevationChange;
	float clampedNewElevation = FMath::Clamp(newElevation, minElevationDegrees, maxElevationDegrees);
	//UE_LOG(LogTemp, Warning, TEXT("Found aim solution, New elevation is %f "), clampedNewElevation);
	SetRelativeRotation(FRotator(clampedNewElevation,0,0));
}


