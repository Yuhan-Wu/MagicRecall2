// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyEye.h"
#include "ProjectileEye.h"
#include "GameFramework/PlayerController.h"
#include "Components/SphereComponent.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

// Sets default values
AEnemyEye::AEnemyEye()
{

}

void AEnemyEye::move_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("%s is moving towards %s"), *GetName(), *getMoveTarget()->GetName());
}

void AEnemyEye::receiveDamage_Implementation()
{
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

	//FRotator MuzzleRotationNinety = EyeRotation.Add(0, 90, 0);
	AProjectileEye* ProjectileNinetyDegrees = GetWorld()->SpawnActor< AProjectileEye >(MuzzleLocation, MuzzleRotation, SpawnParams);
	//FRotator MuzzleRotationNegNinety = EyeRotation.Add(0, -180, 0);
	//AProjectileEye* ProjectileNegNinetyDegrees = GetWorld()->SpawnActor< AProjectileGhost >(MuzzleLocation, MuzzleRotationNegNinety, SpawnParams);
	UE_LOG(LogTemp, Log, TEXT("Eye Launches Projectiles"));
	//UE_LOG(LogTemp, Log, TEXT("%s is attacking"), *GetName());
}

