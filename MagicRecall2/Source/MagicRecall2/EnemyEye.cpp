// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyEye.h"
#include "GameFramework/PlayerController.h"
#include "Components/SphereComponent.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include <EngineGlobals.h>
#include "MonsterInc.h"
#include "EngineUtils.h"
#include <Runtime/Engine/Classes/Engine/Engine.h>

// Sets default values
AEnemyEye::AEnemyEye()
{
	/*
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent((USceneComponent *)GetCapsuleComponent());
	ProjectileMovementComponent->InitialSpeed = 0;
	ProjectileMovementComponent->MaxSpeed = Speed*2;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;
	ProjectileMovementComponent->ProjectileGravityScale = 0;
	*/
}

void AEnemyEye::move_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("%s is moving towards %s"), *GetName(), *getMoveTarget()->GetName());
}

void AEnemyEye::receiveDamage_Implementation()
{
	for (TActorIterator<AMonsterInc> It(GetWorld()); It; ++It)
	{
		It->MonsterNumDecrease();
	}
	Destroy();
}

void AEnemyEye::attack_Implementation()
{
	//Add complex projectiles
	FVector EyeLocation;
	FRotator EyeRotation;
	GetActorEyesViewPoint(EyeLocation, EyeRotation);

	// To world location
	FVector MuzzleLocation = EyeLocation; //+ FTransform(GhostRotation).TransformVector(MuzzleOffset);
	//MuzzleLocation.Z -= 10;
	FRotator MuzzleRotation = EyeRotation;


	UWorld* World = GetWorld();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = Instigator;

	AProjectileEye* ProjectileNinetyDegrees = GetWorld()->SpawnActor< AProjectileEye >(Projectile, MuzzleLocation, MuzzleRotation, SpawnParams);
	ProjectileNinetyDegrees->Eye = this;
	UE_LOG(LogTemp, Log, TEXT("Eye Launches Projectiles"));
	//UE_LOG(LogTemp, Log, TEXT("%s is attacking"), *GetName());
	
}

