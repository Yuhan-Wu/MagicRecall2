// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpider.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/SphereComponent.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>



// Sets default values
AEnemySpider::AEnemySpider()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//setMoveTarget(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation());
	//setMoveTarget(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());
	//GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	//setMoveTarget();
	//setMoveTarget(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation());
	

		// Our root component will be a sphere that reacts to physics
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	// Create and position a mesh component so we can see where our sphere is
	UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
		SphereVisual->SetWorldScale3D(FVector(0.8f));
	}

}

// Called when the game starts or when spawned
void AEnemySpider::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemySpider::Tick(float DeltaTime)
{
	//setMoveTarget(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());
	//move_Implementation();
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemySpider::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemySpider::move_Implementation()
{
	//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("Debug Player Position: x: %f, y: %f"), getMoveTarget().X, getMoveTarget().Y));
	//SetActorLocation(getMoveTarget(), true);
	//AddMovementInput(this->GetActorLocation() - getMoveTarget(), 100.f);
	//ConsumeMovementInputVector();
	UE_LOG(LogTemp, Log, TEXT("%s is moving"), *GetName());
}

void AEnemySpider::receiveDamage_Implementation()
{
}

void AEnemySpider::attack_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("%s is attacking"), *GetName());
}

