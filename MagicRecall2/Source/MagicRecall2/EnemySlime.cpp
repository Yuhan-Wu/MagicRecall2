// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySlime.h"
#include "GameFramework/PlayerController.h"
#include "Components/SphereComponent.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include <EngineGlobals.h>
#include "EngineUtils.h"
#include "MonsterInc.h"
#include <Runtime/Engine/Classes/Engine/Engine.h>

int AEnemySlime::Slime_Num = 0;

// Sets default values
AEnemySlime::AEnemySlime()
{
 	

}

void AEnemySlime::move_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("%s is moving towards %s"), *GetName(), *getMoveTarget()->GetName());
}

void AEnemySlime::receiveDamage_Implementation()
{
	for (TActorIterator<AMonsterInc> It(GetWorld()); It; ++It)
	{
		It->MonsterNumDecrease();
	}
	Slime_Num--;
	Destroy();
}

void AEnemySlime::attack_Implementation()
{
	//Add interaction with braziers
	UE_LOG(LogTemp, Log, TEXT("%s has extinguished %s"), *GetName(), *getAttackTarget()->GetName());
}

void AEnemySlime::PlaySound() {
	UAudioComponent* audio = Cast<UAudioComponent>(GetComponentByClass(UAudioComponent::StaticClass()));
	audio->Play();
}
