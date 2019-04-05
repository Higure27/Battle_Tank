// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class URadialForceComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	void LaunchProjectile(float speed);

private:

	UProjectileMovementComponent* projectileMovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Firing")
	UStaticMeshComponent* collisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Firing")
	UParticleSystemComponent* launchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Firing")
	UParticleSystemComponent* hitBlast = nullptr;

	//Fires Impulse
	UPROPERTY(VisibleAnywhere, Category = "Firing")
	URadialForceComponent* explosionForce = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float destroyDelay = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float hitDamage = 20.f;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit);

	void DestroyProjectile();
	
};
