// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	lastFiredTime = GetWorld()->GetTimeSeconds();

	tankAimingComponent = FindComponentByClass<UTankAimingComponent>();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector aimLocation)
{	
	if (!ensure(tankAimingComponent))
	{
		//UE_LOG(LogTemp, Error, TEXT("Tank: Tank aiming component not found"));
		return;
	}
	//Needs launchSpeed for proper firing 
	tankAimingComponent->AimAt(aimLocation,launchSpeed);
}

void ATank::Fire()
{
	if (!ensure(barrel)) { return; }

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
	//tankAimingComponent->SetBarrelReference(barrelToRefer);
	barrel = barrelToRefer;
}

/*void ATank::SetTurretReference(UTankTurret* turrretToRefer)
{
	tankAimingComponent->SetTurretReference(turrretToRefer);
}*/