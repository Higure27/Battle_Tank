// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"


class UTankTrack;
/**
 * In charge of driving the tank tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	

public:

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void initialize(UTankTrack* rightTrackToRef, UTankTrack* leftTrackToRef);

	//controllerThrow is how far forward or backwards the control is moved 
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float controlThrow);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendTurnRight(float controlThrow);

	

private:

	UTankTrack* rightTrack = nullptr;
	UTankTrack* leftTrack = nullptr;

	//Called from the pathfinding logic by the AI tank controllers (MoveToActor)
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	
};
