// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	collisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh Component"));
	SetRootComponent(collisionMesh);
	collisionMesh->SetNotifyRigidBodyCollision(true);
	collisionMesh->SetVisibility(false);

	projectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movment Component"));
	projectileMovementComponent->bAutoActivate = false;

	launchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast Particle System"));
	launchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	hitBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Hit Blast Particle System"));
	hitBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	hitBlast->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	collisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
}

// Called every frame
/*void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}*/

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	launchBlast->Deactivate();
	hitBlast->Activate();

}

void AProjectile::LaunchProjectile(float speed)
{
	projectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector* speed);
	projectileMovementComponent->Activate();
}

