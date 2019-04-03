// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward decleration
class UTankBarrel; 
class UTankTurret;

UENUM()
enum class EFIRINGSTATUS :uint8
{
	Reloading,
	Aiming,
	LockedOn
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void initialize(UTankBarrel* barrelToRef, UTankTurret* turretToRef);

	void AimAt(FVector aimWorldSpaceLocation);

	//void SetBarrelReference(UTankBarrel* barrelToRefer);

	//void SetTurretReference(UTankTurret* turretToRefer);

protected:

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFIRINGSTATUS currentFiringStatus = EFIRINGSTATUS::Aiming;

private:

	UTankBarrel* barrel = nullptr;

	UTankTurret* turret = nullptr;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float launchSpeed = 5000.f;

	void MoveBarrelTowards(FVector aimDirection);

	
	
};
