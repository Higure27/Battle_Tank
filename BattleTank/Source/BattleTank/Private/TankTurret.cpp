// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Rotate(float relativeSpeed)
{
	relativeSpeed = FMath::Clamp(relativeSpeed, -1.f, 1.f);
	//Framerate Independent by using delta 
	float rotationChange = relativeSpeed * maxDegreesPerSecond* GetWorld()->DeltaTimeSeconds;
	float newRotation = RelativeRotation.Yaw + rotationChange;
	UE_LOG(LogTemp, Warning, TEXT("Found aim solution, New n is %f "), newRotation);
	SetRelativeRotation(FRotator(0, newRotation, 0));
}


