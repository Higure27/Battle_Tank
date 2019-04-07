// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"
#include "SprungWheel.h"
#include "SpawnPointComponent.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
}


void UTankTrack::SetThrottle(float throttle)
{
	float currentThrottle = FMath::Clamp<float>(throttle, -1.f, 1.f);
	DriveTrack(currentThrottle);
}

void UTankTrack::DriveTrack(float currentThrottle)
{
	float forceApplied =  currentThrottle * trackMaxDrivingForce;
	auto trackWheels = GetTrackWheels();
	int32 numOfWheels = trackWheels.Num();
	float forcePerWheel = forceApplied / static_cast<float>(numOfWheels);
	for (ASprungWheel* wheel : trackWheels)
	{
		wheel->AddDrivingForce(forcePerWheel);
	}


}

TArray<ASprungWheel*> UTankTrack::GetTrackWheels() const
{
	TArray <USceneComponent*> childrenSpawnPoints;
	TArray<ASprungWheel*> trackWheels;

	GetChildrenComponents(true, childrenSpawnPoints);

	for (USceneComponent* spawnPoint : childrenSpawnPoints)
	{
		USpawnPointComponent* castedSpawnPoint = Cast<USpawnPointComponent>(spawnPoint);
		if (!castedSpawnPoint) { continue; }

		AActor* spawnedActor = castedSpawnPoint->GetSpawnedActor();
		
		ASprungWheel* wheelToAdd = Cast<ASprungWheel>(spawnedActor);
		if (wheelToAdd)
		{
			trackWheels.Add(wheelToAdd);
		}
	}

	return trackWheels;
}

