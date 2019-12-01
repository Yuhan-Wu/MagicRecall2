// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileGhost.h"

// Sets default values
AProjectileGhost::AProjectileGhost()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	USphereComponent* CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(10.0f);
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("ProjectileGhost"));

	RootComponent = CollisionComponent;

	UProjectileMovementComponent* ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = Speed;
	ProjectileMovementComponent->MaxSpeed = Speed;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;
	ProjectileMovementComponent->ProjectileGravityScale = 0;

}

// Called when the game starts or when spawned
void AProjectileGhost::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectileGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

