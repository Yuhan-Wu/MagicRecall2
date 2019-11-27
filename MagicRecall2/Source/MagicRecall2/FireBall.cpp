// Fill out your copyright notice in the Description page of Project Settings.


#include "FireBall.h"
#include "Enemy.h"
#include "MagicRecall2Character.h"

// Sets default values
AFireBall::AFireBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(15.0f);
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Fireball_Attack"));
	
	RootComponent = CollisionComponent;

	TotalDistance = 0;
	bool isBack = false;
	MaxDistance = 500;
	Speed = 500;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = Speed;
	ProjectileMovementComponent->MaxSpeed = Speed;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;
	ProjectileMovementComponent->ProjectileGravityScale = 0;

	
}

AFireBall::AFireBall(float total_distance,float speed) {
	AFireBall();
	MaxDistance = total_distance;
	Speed = speed;
}

// Called when the game starts or when spawned
void AFireBall::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AFireBall::OnOverlap);
}

// Called every frame
void AFireBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Get back
	TotalDistance += DeltaTime * Speed;
	if (TotalDistance >= MaxDistance) {
		//UE_LOG(LogTemp, Log, TEXT("Back"));
		isBack = true;
	}

	if (isBack) {
		// UE_LOG(LogTemp, Log, TEXT("Back"));
		if (Wizard == nullptr) {
			UE_LOG(LogTemp, Log, TEXT("Fail"));
		}
		FVector Wizard_Location = Wizard->GetActorLocation();
		FVector Fireball_Location = this->GetActorLocation();
	
		FVector Direction = Wizard_Location - Fireball_Location;
		// UE_LOG(LogTemp, Log, TEXT("%s"),*Wizard_Location.ToCompactString());
		ProjectileMovementComponent->Velocity = Direction * ProjectileMovementComponent->InitialSpeed/700;
	}

}

void AFireBall::MahouInDirection(const FVector& ShootDirection) {
	// InitialDirection = ShootDirection;
	//UE_LOG(LogTemp, Log, TEXT("SHOULD BE TWICE"));
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void AFireBall::SetHome(AActor* Wizard) {
	AFireBall::Wizard = Wizard;
}

// When fireball returns
void AFireBall::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	UE_LOG(LogTemp, Log, TEXT("OVERLAP"));
	if (OtherActor != this && Cast<AMagicRecall2Character>(OtherActor))
	{
		// UE_LOG(LogTemp, Log, TEXT("OVERLAP"));
		Destroy();
	}
	else if (OtherActor != this && Cast<IEnemy>(OtherActor)) {
		IEnemy* cur_monster = Cast<IEnemy>(OtherActor);
		cur_monster->receiveDamage();
	}
}

void AFireBall::SetSpeed(float speed) {
	Speed = speed;
	ProjectileMovementComponent->InitialSpeed = Speed;
	ProjectileMovementComponent->MaxSpeed = Speed;
}

void AFireBall::SetDistance(float distance) {
	MaxDistance = distance;
}
