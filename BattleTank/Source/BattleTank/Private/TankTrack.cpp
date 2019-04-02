// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float throttle)
{
	FVector forceApplied = GetForwardVector() * throttle * trackMaxDrivingForce;
	FVector forceLocation = GetComponentLocation();
	//cast to UPrimitiveComponent to apply physic based forces
	UPrimitiveComponent* tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}


