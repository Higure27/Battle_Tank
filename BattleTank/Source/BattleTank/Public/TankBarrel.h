// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent),hidecategories ="Collision")
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//-1 is max downward movment +1 is max upward movment
	void Elevate(float releativeSpeed);

private:

	UPROPERTY(EditAnywhere,Category = SetUp)
	float maxDegreesPerSecond = 5.f;//intial value
	
	UPROPERTY(EditAnywhere, Category = SetUp)
	float minElevationDegrees = 0.f;//intial value

	UPROPERTY(EditAnywhere, Category = SetUp)
	float maxElevationDegrees = 45.f;//intial value

	
	
};
