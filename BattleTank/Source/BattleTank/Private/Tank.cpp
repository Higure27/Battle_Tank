// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"


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

void ATank::SetBarrelReference(UTankBarrel* barrelToRefer)
{
	tankAimingComponent->SetBarrelReference(barrelToRefer);
}

void ATank::SetTurretReference(UTankTurret* turrretToRefer)
{
	tankAimingComponent->SetTurretReference(turrretToRefer);
}