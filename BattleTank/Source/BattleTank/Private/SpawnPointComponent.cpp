// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnPointComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
USpawnPointComponent::USpawnPointComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpawnPointComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* newActor = GetWorld()->SpawnActorDeferred<AActor>(spawnClass, GetComponentTransform());
	if (!newActor) { return; }
	newActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	UGameplayStatics::FinishSpawningActor(newActor, GetComponentTransform());
}


// Called every frame
void USpawnPointComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

