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
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UE_LOG(LogTemp, Log, TEXT("Constructor"));
	//Creates a placeholder sphere for ghosts
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.0f);
	SphereComponent->SetCollisionProfileName(TEXT("EnemyGhost"));
	SphereComponent->SetCanEverAffectNavigation(false);

	// Create and position a mesh component so we can see where our sphere is
	UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->SetupAttachment(RootComponent);
	SphereVisual->SetCanEverAffectNavigation(false);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		SphereVisual->SetWorldScale3D(FVector(0.8f));
	}
}

// Called when the game starts or when spawned
void AEnemyGhost::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//attack();
}

// Called to bind functionality to input
void AEnemyGhost::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

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



