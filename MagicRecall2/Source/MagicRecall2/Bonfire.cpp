// Fill out your copyright notice in the Description page of Project Settings.


#include "Bonfire.h"
#include "MagicRecall2Character.h"

// Sets default values
ABonfire::ABonfire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Bonfire"));

	RootComponent = CollisionComponent;
}

// Called when the game starts or when spawned
void ABonfire::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABonfire::OnOverlap);
}

// Called every frame
void ABonfire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABonfire::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	// UE_LOG(LogTemp, Log, TEXT("Enter"));
	if (OtherActor != this && Cast<AMagicRecall2Character>(OtherActor)&&!isLit)
	{
		isLit = true;
		AMagicRecall2Character* wizard = Cast<AMagicRecall2Character>(OtherActor);
		wizard->PowerUp();
		// UE_LOG(LogTemp, Log, TEXT("POWERUP"));
		// TODO: light it up
	}
	// TODO: deal with slime
}

