// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

//Forward declerations:
class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

protected:

	//How close the AI tank can get to the player
	UPROPERTY(EditDefaultsOnly,Category = "Setup")
	float acceptanceRadius = 7000;

private:

	APawn * targetTank = nullptr;

	UTankAimingComponent * aimingComponent = nullptr;
	
	
};
