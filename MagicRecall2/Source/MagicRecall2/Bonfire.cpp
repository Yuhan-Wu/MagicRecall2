// Fill out your copyright notice in the Description page of Project Settings.


#include "Bonfire.h"
#include "EnemySlime.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerController.h"

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
	particles = Cast<UParticleSystemComponent>(GetComponentByClass(UParticleSystemComponent::StaticClass()));
	particles->DeactivateSystem();
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
		particles->ActivateSystem();
		// UE_LOG(LogTemp, Log, TEXT("POWERUP"));
	}
	else if (OtherActor != this && Cast<AEnemySlime>(OtherActor)) {
		AEnemySlime* slime = Cast<AEnemySlime>(OtherActor);
		slime->receiveDamage();
		if (isLit) {
			isLit = false;
			for (TActorIterator<AMagicRecall2Character> wizard(GetWorld()); wizard; ++wizard)
			{
				// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
				if (wizard) {
					wizard->BackToMuggle();
					particles->DeactivateSystem();
				}
			}
		}
	}
}

void ABonfire::ReceiveTwitchInput(AMagicRecall2Character* wizard,FName username) {
	// UE_LOG(LogTemp, Log, TEXT("POWERUP"));
	if (!isLit) {
		isLit = true;
		user_name = username;
		wizard->PowerUp();
		particles->ActivateSystem();
	}
}

