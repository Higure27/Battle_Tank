// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	tankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Tank Aiming Component"));

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	lastFiredTime = GetWorld()->GetTimeSeconds();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector aimLocation)
{	//needs launchSpeed for proper firing 
	tankAimingComponent->AimAt(aimLocation,launchSpeed);
}

void ATank::Fire()
{
	if (!barrel) { return; }

	bool bIsReloaded = (GetWorld()->GetTimeSeconds() - lastFiredTime) > reloadTimeInSeconds;

	if (bIsReloaded)
	{
		FVector projectileLocation = barrel->GetSocketLocation(FName("Projectile"));
		FRotator projectileRotation = barrel->GetSocketRotation(FName("Projectile"));

		//Spawn a projectile at the socket location on the barrel
		AProjectile* firedProjectile = GetWorld()->SpawnActor<AProjectile>(projectileBP, projectileLocation, projectileRotation);

		lastFiredTime = GetWorld()->GetTimeSeconds();
		firedProjectile->LaunchProjectile(launchSpeed);
	}

}

void ATank::SetBarrelReference(UTankBarrel* barrelToRefer)
{
	tankAimingComponent->SetBarrelReference(barrelToRefer);
	barrel = barrelToRefer;
}

void ATank::SetTurretReference(UTankTurret* turrretToRefer)
{
	tankAimingComponent->SetTurretReference(turrretToRefer);
}