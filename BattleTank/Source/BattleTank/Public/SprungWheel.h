// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class UPhysicsConstraintComponent;
class USphereComponent;

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Force applied on wheel, can be positive or negative
	void AddDrivingForce(float forceMagnitude);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, Category = "Spring")
	USphereComponent* wheel = nullptr;

	//Mass to Axle constraint
	UPROPERTY(VisibleAnywhere, Category = "Spring")
	UPhysicsConstraintComponent* massAxleConstraint = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Spring")
	USphereComponent* axle = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Spring")
	UPhysicsConstraintComponent* axleWheelConstraint = nullptr;

	float totalForceMagnitudeInFrame = 0;

	void SetupConstraints();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void ApplyForce();

	
};