// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Enemy.h"
#include "ProjectileGhost.generated.h"

UCLASS()
class MAGICRECALL2_API AProjectileGhost : public AActor, public IEnemy
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileGhost();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	float Speed = 400;

};
