// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;// TODO: Check if TAC should tick

	// ...
}


void UTankAimingComponent::AimAt(FVector aimWorldSpaceLocation, float launchSpeed)
{
	if (!barrel)
	{
		UE_LOG(LogTemp, Error, TEXT("Barrel not found"));
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
		auto currentTime = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f :Found aim solution"), currentTime);
	}
	else
	{
		auto currentTime = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f : NO aim solution"), currentTime);
	}
	//else do nothing
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* barrelToRefer)
{
	barrel = barrelToRefer;
}

//Takes in the aim direction vector and move tank barrel accordingly
void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	// Get barrel rotation 
	FRotator barrelRotator = barrel->GetForwardVector().Rotation();
	FRotator aimAsRotator = aimDirection.Rotation();
	//Difference in rotation between barrel and aim rotation
	FRotator DeltaRotator = aimAsRotator - barrelRotator;
	


	//Move barrel  into new position 
	barrel->Elevate(1.0f);
	//TODO:Create UTankBarrelClass for barrel movment
}