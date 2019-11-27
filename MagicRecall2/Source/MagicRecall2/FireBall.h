// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "FireBall.generated.h"

UCLASS()
class MAGICRECALL2_API AFireBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireBall();
	AFireBall(float total_distance,float speed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	bool isBack;
	
	AActor* Wizard;

	float Speed;
	float TotalDistance;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetHome(AActor*);

	// Shoot
	void MahouInDirection(const FVector& ShootDirection);

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere)
	float MaxDistance;

	UFUNCTION()
	void OnOverlap (UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetSpeed(float);
	void SetDistance(float);

	
};
