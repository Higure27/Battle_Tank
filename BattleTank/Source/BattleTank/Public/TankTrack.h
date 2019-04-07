// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

//Forward declerations:
class ASprungWheel;

/**
 * TankTrack is used to set max driving force, and applay forces to the tank
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	
	UTankTrack();
	//Sets throttle between -1 and 1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float throttle);
	//Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly)
	float trackMaxDrivingForce = 400000;// Considering tank is 40 tons and 1 g acceleration

protected:

	virtual void BeginPlay() override;

private:

	void DriveTrack(float currentThrottle);

	TArray<ASprungWheel*> GetTrackWheels() const;
	
};