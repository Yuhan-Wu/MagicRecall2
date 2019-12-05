// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyGhost.h"
#include "GameFramework/PlayerController.h"
#include "Components/SphereComponent.h"

#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include <EngineGlobals.h>
#include "ProjectileGhost.h"
#include "MonsterInc.h"
#include "Engine.h"
#include "Misc/App.h"
#include <Runtime/Engine/Classes/Engine/Engine.h>



int AEnemyGhost::Ghost_Num = 0;

// Sets default values
AEnemyGhost::AEnemyGhost()
{
	
}

void AEnemyGhost::BeginPlay() {
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(handler, this, &AEnemyGhost::attack_Implementation, 2, true);
}

void AEnemyGhost::move_Implementation()
{
	timeUntilCanFlip -= GetWorld()->GetDeltaSeconds();
	if (((GetActorLocation().X > 630 || GetActorLocation().X < -2050) || (GetActorLocation().Y > 4320 || GetActorLocation().Y < -1130)) && timeUntilCanFlip < 0) { //up down flip
		UE_LOG(LogTemp, Log, TEXT("Flip"));
		SetActorRotation(FRotator(GetActorRotation().Pitch,((int)GetActorRotation().Yaw + 180)%360,GetActorRotation().Roll));
		timeUntilCanFlip = 10;
	}

	SetActorLocation(GetActorLocation() + (GetActorForwardVector() * 2.5), true);
	//AddActorWorldRotation(180);
}

void AEnemyGhost::receiveDamage_Implementation()
{
	health -= 1;
	if (health <= 0) {
		mtx.lock();
		for (TActorIterator<AMonsterInc> It(GetWorld()); It; ++It)
		{
			It->MonsterNumDecrease();
			break;
		}
		Ghost_Num--;
		Destroy();
		mtx.unlock();
	}
}

void AEnemyGhost::attack_Implementation()
{
	//This should shoot projectiles
	//UE_LOG(LogTemp, Log, TEXT("%s is attacking"), *GetName());// Get location & rotation
	
	FVector GhostLocation;
	FRotator GhostRotation;
	GetActorEyesViewPoint(GhostLocation, GhostRotation);

	// To world location
	FVector MuzzleLocation = GhostLocation + FTransform(GhostRotation).TransformVector(FVector(40, 0, 0));
	//MuzzleLocation.Z -= 10;
	FRotator MuzzleRotation = GhostRotation;

	FRotator MuzzleRotationNinety = GhostRotation.Add(0, 90, 0);
	AProjectileGhost* ProjectileNinetyDegrees = GetWorld()->SpawnActor< AProjectileGhost >(Projectile, MuzzleLocation, MuzzleRotationNinety);
	FRotator MuzzleRotationNegNinety = GhostRotation.Add(0, -180, 0);
	AProjectileGhost* ProjectileNegNinetyDegrees = GetWorld()->SpawnActor< AProjectileGhost >(Projectile, MuzzleLocation, MuzzleRotationNegNinety);
}

void AEnemyGhost::PlaySound() {
	UAudioComponent* audio = Cast<UAudioComponent>(GetComponentByClass(UAudioComponent::StaticClass()));
	audio->Play();
}



