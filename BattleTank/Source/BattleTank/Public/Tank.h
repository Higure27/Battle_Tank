// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Forward declerations
class UTankAimingComponent;
class UTankMovementComponent;
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(FVector aimLocation);

	UFUNCTION(BlueprintCallable,Category = Controls)
	void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent *tankAimingComponent = nullptr;
	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent *tankMovmentComponent = nullptr;

private:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* barrelToRefer);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* turrretToRefer);

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> projectileBP;

	UPROPERTY(EditAnywhere, Category = Firing)
	float launchSpeed = 5000.f;

	//Local barrel reference for firing projectile
	UTankBarrel* barrel = nullptr;
	
	UPROPERTY(EditAnywhere, Category = Firing)
	float reloadTimeInSeconds = 3.f;

	double lastFiredTime = 0;
};
