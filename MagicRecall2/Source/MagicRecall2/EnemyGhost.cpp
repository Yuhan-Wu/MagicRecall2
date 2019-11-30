// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyGhost.h"
#include "GameFramework/PlayerController.h"
#include "Components/SphereComponent.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include <EngineGlobals.h>
#include "ProjectileGhost.h"
#include <Runtime/Engine/Classes/Engine/Engine.h>

// Sets default values
AEnemyGhost::AEnemyGhost()
{

}

void AEnemyGhost::move_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("%s is moving"), *GetName()); //No target
}

void AEnemyGhost::receiveDamage_Implementation()
{
	Destroy();
}

void AEnemyGhost::attack_Implementation()
{
	//This should shoot projectiles
	//UE_LOG(LogTemp, Log, TEXT("%s is attacking"), *GetName());// Get location & rotation
	FVector GhostLocation;
	FRotator GhostRotation;
	GetActorEyesViewPoint(GhostLocation, GhostRotation);

	// To world location
	FVector MuzzleLocation = GhostLocation; //+ FTransform(GhostRotation).TransformVector(MuzzleOffset);
	//MuzzleLocation.Z -= 10;
	FRotator MuzzleRotation = GhostRotation;
	
	
	UWorld* World = GetWorld();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = Instigator;

	FRotator MuzzleRotationNinety = GhostRotation.Add(0, 90, 0);
	AProjectileGhost* ProjectileNinetyDegrees = GetWorld()->SpawnActor< AProjectileGhost >(MuzzleLocation, MuzzleRotationNinety, SpawnParams);
	FRotator MuzzleRotationNegNinety = GhostRotation.Add(0, -180, 0);
	AProjectileGhost* ProjectileNegNinetyDegrees = GetWorld()->SpawnActor< AProjectileGhost >(MuzzleLocation, MuzzleRotationNegNinety, SpawnParams);
	UE_LOG(LogTemp, Log, TEXT("Ghost Launches Projectiles"));
}



