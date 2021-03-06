// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::initialize(UTankTrack* rightTrackToRef, UTankTrack* leftTrackToRef)
{
	rightTrack = rightTrackToRef;
	leftTrack = leftTrackToRef;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//Replacing functionality therefore no need for Super call
	FVector tankCurrentForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector tankForwardIntent = MoveVelocity.GetSafeNormal();
	
	
	float vectorProjection = FVector::DotProduct(tankForwardIntent, tankCurrentForward);
	IntendMoveForward(vectorProjection);
	

	float vectorPerp = FVector::CrossProduct(tankCurrentForward,tankForwardIntent).Z;
	IntendTurnRight(vectorPerp);
}

void UTankMovementComponent::IntendMoveForward(float controlThrow)
{
	if (!ensure(rightTrack && leftTrack))
	{ 
		UE_LOG(LogTemp, Error, TEXT("Either left or right tracks were not found"))
		return;
	}

	rightTrack->SetThrottle(controlThrow);
	leftTrack->SetThrottle(controlThrow);

}

void UTankMovementComponent::IntendTurnRight(float controlThrow)
{
	if (!ensure(rightTrack && leftTrack))
	{
		UE_LOG(LogTemp, Error, TEXT("Either left or right tracks were not found"))
		return;
	}

	rightTrack->SetThrottle(-controlThrow);
	leftTrack->SetThrottle(controlThrow);
}

