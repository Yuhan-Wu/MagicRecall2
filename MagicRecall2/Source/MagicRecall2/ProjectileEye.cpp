// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileEye.h"

// Sets default values
AProjectileEye::AProjectileEye()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(10.0f);
	

	RootComponent = CollisionComponent;

	// Create and position a mesh component so we can see the projectiles
	UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->SetupAttachment(RootComponent);
	SphereVisual->SetCanEverAffectNavigation(false);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		SphereVisual->SetWorldScale3D(FVector(0.4f));
	}

	//Just ignore this bit
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 0;
	ProjectileMovementComponent->MaxSpeed = Speed*2;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;
	ProjectileMovementComponent->ProjectileGravityScale = 0;

}

// Called when the game starts or when spawned
void AProjectileEye::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectileEye::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// circle around eye
	FVector NewLocation = this->GetActorLocation();//FVector(0, 0, 800);

	// radius increases
	FVector Radius = FVector(i, 0, 0);

	// angle increases by 1 every frame
	AngleAxis+= 1.5;

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

