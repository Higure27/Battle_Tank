// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

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
		//UE_LOG(LogTemp, Warning, TEXT("%s Firing at the direction: %s"), *tankName,*aimDirection.ToString());
		MoveBarrelTowards(aimDirection);
	}
	//else do nothing
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* barrelToRefer)
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
	UE_LOG(LogTemp, Warning, TEXT("%s Rotation needed"), *DeltaRotator.ToString());


	//Move barrel  into new position 
	//TODO:Create UTankBarrelClass for barrel movment
}