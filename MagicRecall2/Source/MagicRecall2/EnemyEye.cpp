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
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creates a placeholder sphere for eyes
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.0f);
	SphereComponent->SetCollisionProfileName(TEXT("EnemyEye"));
	SphereComponent->SetCanEverAffectNavigation(false);

	// Create and position a mesh component so we can see where our sphere is
	UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->SetupAttachment(RootComponent);
	SphereVisual->SetCanEverAffectNavigation(false);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
		SphereVisual->SetWorldScale3D(FVector(0.9f));
	}

}

// Called when the game starts or when spawned
void AEnemyEye::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyEye::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//attack();
}

// Called to bind functionality to input
void AEnemyEye::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyEye::move_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("%s is moving towards %s"), *GetName(), *getMoveTarget()->GetName());
}

void AEnemyEye::receiveDamage_Implementation()
{
	Destroy(this);
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
