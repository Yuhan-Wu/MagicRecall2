// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyEye.h"
#include "ProjectileEye.h"
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

void AEnemyEye::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	FVector NewLocation = this->GetActorLocation();//FVector(0, 0, 800);

	// radius increases
	FVector Radius = FVector(i, 0, 0);

	// angle increases by 1 every frame
	AngleAxis += 1.5;

	// prevent number from growind indefinitely
	if (AngleAxis > 360.0f) {

		AngleAxis = 1;
	}

	FVector RotateValue = Radius.RotateAngleAxis(AngleAxis, FVector(0, 0, 1));

	NewLocation.X += RotateValue.X;
	NewLocation.Y += RotateValue.Y;
	NewLocation.Z += RotateValue.Z;

	SetActorLocation(NewLocation);
	i += .04;
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
	/*
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
	*/
	FVector NewLocation = this->GetActorLocation();//FVector(0, 0, 800);

	// radius increases
	FVector Radius = FVector(i, 0, 0);

	// angle increases by 1 every frame
	AngleAxis += 1.5;

	// prevent number from growind indefinitely
	if (AngleAxis > 360.0f) {

		AngleAxis = 1;
	}

	FVector RotateValue = Radius.RotateAngleAxis(AngleAxis, FVector(0, 0, 1));

	NewLocation.X += RotateValue.X;
	NewLocation.Y += RotateValue.Y;
	NewLocation.Z += RotateValue.Z;

	SetActorLocation(NewLocation);
	i += .04;
}

