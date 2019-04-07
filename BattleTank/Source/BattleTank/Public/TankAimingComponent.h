// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward decleration
class UTankBarrel; 
class UTankTurret;
class AProjectile;

UENUM()
enum class EFIRINGSTATUS :uint8
{
	Reloading,
	Aiming,
	LockedOn,
	OutOfAmmo
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

	UFUNCTION(BlueprintCallable, Category = "Controls")
	void Fire();

	EFIRINGSTATUS GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetBulletsLeft() const;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFIRINGSTATUS currentFiringStatus = EFIRINGSTATUS::Reloading;

private:

	UTankBarrel* barrel = nullptr;

	UTankTurret* turret = nullptr;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float launchSpeed = 5000.f;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float reloadTimeInSeconds = 1.5f;

	double lastFiredTime = 0;

	UPROPERTY(EditAnywhere, Category = "Firing")
	int32 bulletsLeft = 20;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> projectileBP;

	FVector aimDirection;

	void MoveBarrelTowards(FVector givenAimDirection);

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	bool IsBarrelMoving();
	
};
