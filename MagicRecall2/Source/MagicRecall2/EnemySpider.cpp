// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpider.h"
#include "Engine/World.h"
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
AEnemySpider::AEnemySpider()
{
	//setMoveTarget(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation());
	//setMoveTarget(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());
	//GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	//setMoveTarget();
	//setMoveTarget(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation());
	

	//Creates a placeholder sphere for spiders
	/*USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));
	SphereComponent->SetCanEverAffectNavigation(false);*/

}

void AEnemySpider::move_Implementation()
{
	//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("Debug Player Position: x: %f, y: %f"), getMoveTarget().X, getMoveTarget().Y));
	//SetActorLocation(getMoveTarget(), true);
	//AddMovementInput(this->GetActorLocation() - getMoveTarget(), 100.f);
	//ConsumeMovementInputVector();
	UE_LOG(LogTemp, Log, TEXT("%s is moving towards %s"), *GetName(), *getMoveTarget()->GetName());
}

void AEnemySpider::receiveDamage_Implementation()
{
	for (TActorIterator<AMonsterInc> It(GetWorld()); It; ++It)
	{
		It->MonsterNumDecrease();
	}
	Destroy();
}

void AEnemySpider::attack_Implementation()
{
	m_bAttacking = true;
	UE_LOG(LogTemp, Log, TEXT("%s is attacking %s"), *GetName(), *getAttackTarget()->GetName());
}
