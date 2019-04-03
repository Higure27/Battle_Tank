// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

//Forward declerations:
class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* aimCompRef);

private:

	UTankAimingComponent* aimingComponent = nullptr;

	///Aim the tank barrel towards the crosshair, where the crosshair intersects with the world
	void AimTowardsCrossHair();

	bool GetSightHitLocation(FVector& outHitLocation) const;

	bool GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const;

	bool GetLookVectorHitLocation(FVector lookDirection, FVector& outHitLocation) const;

	UPROPERTY(EditAnywhere)
	float crossHairXLocation = .5f;

	UPROPERTY(EditAnywhere)
	float crossHairYLocation = .33333f;

	UPROPERTY(EditAnywhere)
	float lineTraceRange = 1000000.f;
};

