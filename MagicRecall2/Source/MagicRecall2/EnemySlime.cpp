// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySlime.h"
#include "GameFramework/PlayerController.h"
#include "Components/SphereComponent.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

// Sets default values
AEnemySlime::AEnemySlime()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creates a placeholder sphere for slimes
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.0f);
	SphereComponent->SetCollisionProfileName(TEXT("EnemySlime"));
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
		SphereVisual->SetWorldScale3D(FVector(0.8f));
	}

}

// Called when the game starts or when spawned
void AEnemySlime::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemySlime::Tick(float DeltaTime)
{
	//will need to set target
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemySlime::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemySlime::move_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("%s is moving towards %s"), *GetName(), *getMoveTarget()->GetName());
}

void AEnemySlime::receiveDamage_Implementation()
{
	Destroy();
}

void AEnemySlime::attack_Implementation()
{
	//Add interaction with braziers
	UE_LOG(LogTemp, Log, TEXT("%s has extinguished %s"), *GetName(), *getAttackTarget()->GetName());
}
