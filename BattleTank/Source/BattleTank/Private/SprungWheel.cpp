// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	massAxleConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Physics Constraint Component"));
	SetRootComponent(massAxleConstraint);

	axle = CreateDefaultSubobject<USphereComponent>(FName("Axel"));
	axle->SetupAttachment(massAxleConstraint);

	wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	wheel->SetupAttachment(axle);

	axleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Axle To Wheel Constraint"));
	axleWheelConstraint->SetupAttachment(axle);



}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	SetupConstraints();
}

void ASprungWheel::SetupConstraints()
{
	if (!GetAttachParentActor()) { return; }

	UPrimitiveComponent* tankRoot = Cast< UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!tankRoot) { return; }

	massAxleConstraint->SetConstrainedComponents(tankRoot, NAME_None, axle, NAME_None);
	axleWheelConstraint->SetConstrainedComponents(axle, NAME_None, wheel, NAME_None);
}


// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

