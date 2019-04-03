// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}


void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	
	SideWaysFriction();
	currentThrottle = 0;
}

void UTankTrack::SetThrottle(float throttle)
{
	currentThrottle = FMath::Clamp<float>(currentThrottle + throttle, -1.f, 1.f);
	DriveTrack();
}

void UTankTrack::DriveTrack()
{
	FVector forceApplied = GetForwardVector() * currentThrottle * trackMaxDrivingForce;
	FVector forceLocation = GetComponentLocation();
	//cast to UPrimitiveComponent to apply physic based forces
	UPrimitiveComponent* tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}

//Simulate sideways friction to minimize tank sliding
void UTankTrack::SideWaysFriction()
{
	//The component of speed in the tank right direction
	//If no slippage should be zero
	//If sliding entirely sideways, should be speed
	float slippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	float deltaTime = GetWorld()->DeltaTimeSeconds;
	//Required opposing acceleration in this frame
	FVector correctingAcceleration = -slippageSpeed / deltaTime * GetRightVector();

	UStaticMeshComponent * tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	//calculate and applay sideways force
	FVector correctingForce = correctingAcceleration * tankRoot->GetMass() / 2;//2 Tank tracks

	tankRoot->AddForce(correctingForce);
}

