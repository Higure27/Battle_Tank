// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::initialize(UTankTrack* rightTrackToRef, UTankTrack* leftTrackToRef)
{
	

	rightTrack = rightTrackToRef;
	leftTrack = leftTrackToRef;
}

void UTankMovementComponent::IntendMoveForward(float controlThrow)
{
	if (!rightTrack || !leftTrack)
	{ 
		UE_LOG(LogTemp, Error, TEXT("Either left or right tracks were not found"))
		return;
	}
	rightTrack->SetThrottle(controlThrow);
	leftTrack->SetThrottle(controlThrow);

	//TODO: prevent use of trigers and joysticks at same time
}

void UTankMovementComponent::IntendTurnRight(float controlThrow)
{
	if (!rightTrack || !leftTrack)
	{
		UE_LOG(LogTemp, Error, TEXT("Either left or right tracks were not found"))
			return;
	}
	rightTrack->SetThrottle(-controlThrow);
	leftTrack->SetThrottle(controlThrow);

	//TODO: prevent use of trigers and joysticks at same time
}

