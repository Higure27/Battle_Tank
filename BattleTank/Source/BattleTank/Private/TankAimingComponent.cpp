// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
	// ...
	//currentFiringStatus = EFIRINGSTATUS::Aiming;
}

void UTankAimingComponent::initialize(UTankBarrel* barrelToRef, UTankTurret* turretToRef)
{
	barrel = barrelToRef;
	turret = turretToRef;
}

void UTankAimingComponent::AimAt(FVector aimWorldSpaceLocation)
{
	if (!ensure(barrel))
	{
		UE_LOG(LogTemp, Error, TEXT("Barrel not found"));
		return;
	}

	if (!ensure(turret))
	{
		UE_LOG(LogTemp, Error, TEXT("Turret not found"));
		return;
	}
	FVector outLaunchVelocity;
	FVector startLocation = barrel->GetSocketLocation(FName("Projectile"));

	//Calculate launch velocity

	bool bFoundProjectileDirection = UGameplayStatics::SuggestProjectileVelocity(this, outLaunchVelocity, startLocation, aimWorldSpaceLocation,
		launchSpeed, false, 10.f, .0f, ESuggestProjVelocityTraceOption::DoNotTrace);
	
	if (bFoundProjectileDirection)
	{
		//Get direction as unit vector(takes out magnitude) 
		FVector aimDirection = outLaunchVelocity.GetSafeNormal();
		FString tankName = GetOwner()->GetName();
		MoveBarrelTowards(aimDirection);
		
		//UE_LOG(LogTemp, Warning, TEXT("%f :Found aim solution"), currentTime);
	}
	//else do nothing
}

/*void UTankAimingComponent::SetBarrelReference(UTankBarrel* barrelToRefer)
{
	if (!barrelToRefer) { return; }

	barrel = barrelToRefer;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* turretToRefer)
{
	if (!turretToRefer) { return; }
	turret = turretToRefer;
}*/

//Takes in the aim direction vector and move tank barrel accordingly
void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{	
	if (!ensure(barrel && turret))
	{
		UE_LOG(LogTemp, Error, TEXT("either barrel or turret were not found"));
		return;
	}
	// Get barrel rotation 
	FRotator barrelRotator = barrel->GetForwardVector().Rotation();
	FRotator aimAsRotator = aimDirection.Rotation();
	//Difference in rotation between barrel and aim rotation
	FRotator deltaRotator = aimAsRotator - barrelRotator;
	


	//Move barrel  into new position 
	barrel->Elevate(deltaRotator.Pitch);
	turret->Rotate(deltaRotator.Yaw);
	
}

void UTankAimingComponent::Fire()
{
	if (!ensure(barrel && projectileBP)) { return; }

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