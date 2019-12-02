// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Enemy.h"
#include "ProjectileEye.generated.h"

UCLASS()
class MAGICRECALL2_API AProjectileEye : public AActor, public IEnemy
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileEye();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AActor* Eye;

private:
	float Speed = 400;
	USphereComponent* CollisionComponent;
	UProjectileMovementComponent* ProjectileMovementComponent;
	float i = 10.0f;
	float AngleAxis = 0;

	bool spawned = false;
};
