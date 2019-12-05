// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyEye.h"
#include "GameFramework/PlayerController.h"
#include "Components/SphereComponent.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include <EngineGlobals.h>
#include "MonsterInc.h"
#include "EngineUtils.h"
#include "Engine.h"
#include <Runtime/Engine/Classes/Engine/Engine.h>

int AEnemyEye::Eye_Num = 0;

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
	timer = 0;
	Eye_Num++;
}

void AEnemyEye::BeginPlay() {
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(handler, this, &AEnemyEye::attack_Implementation, 5, true);
}

void AEnemyEye::Tick(float delta) {
	Super::Tick(delta);
	/*
	timer += delta;
	if (timer > 3) {
		timer = 0;
		attack_Implementation();
	}
	*/
}

void AEnemyEye::move_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("%s is moving towards %s"), *GetName(), *getMoveTarget()->GetName());
}

void AEnemyEye::receiveDamage_Implementation()
{
	iFrameTimer -= GetWorld()->GetDeltaSeconds();
	if (iFrameTimer < 0) {
		health -= 1;
		iFrameTimer = .1;
		if (health <= 0) {
			mtx.lock();
			Execute_dead(this);
			for (TActorIterator<AMonsterInc> It(GetWorld()); It; ++It)
			{
				It->MonsterNumDecrease();
			}
			for (AProjectileEye* pro : bullets) {
				pro->Eye = nullptr;
			}
			Eye_Num--;
			mtx.unlock();
			Destroy();
		}
		for (AProjectileEye* pro : bullets) {
			pro->Eye = nullptr;
		}
		Eye_Num--;
		mtx.unlock();
		Destroy();
	}
}

void AEnemyEye::attack_Implementation()
{
	//Add complex projectiles
	FVector EyeLocation;
	FRotator EyeRotation;
	GetActorEyesViewPoint(EyeLocation, EyeRotation);

	// To world location
	FVector MuzzleLocation = EyeLocation+ FTransform(EyeRotation).TransformVector(FVector(500,500,0)); //+ FTransform(GhostRotation).TransformVector(MuzzleOffset);
	//MuzzleLocation.Z -= 10;
	FRotator MuzzleRotation = EyeRotation;
	MuzzleRotation.Pitch += 30.0f;

	AProjectileEye* ProjectileNinetyDegrees = GetWorld()->SpawnActor< AProjectileEye >(Projectile, MuzzleLocation, MuzzleRotation);
	ProjectileNinetyDegrees->Eye = this;
	bullets.push_back(ProjectileNinetyDegrees);
}

void AEnemyEye::PlaySound() {
	UAudioComponent* audio = Cast<UAudioComponent>(GetComponentByClass(UAudioComponent::StaticClass()));
	audio->Play();
}

