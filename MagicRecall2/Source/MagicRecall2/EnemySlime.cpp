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
	user_name = " ";

}

void AEnemySlime::move_Implementation()
{
	
}

void AEnemySlime::receiveDamage_Implementation()
{
	health -= 1;
	if (health <= 0) {
		mtx.lock();
		Execute_dead(this);
		for (TActorIterator<AMonsterInc> It(GetWorld()); It; ++It)
		{
			It->MonsterNumDecrease();
			break;
		}
		Slime_Num--;
		mtx.unlock();
		Destroy();
	}
}

void AEnemySlime::attack_Implementation()
{
	
}

void AEnemySlime::PlaySound() {
	UAudioComponent* audio = Cast<UAudioComponent>(GetComponentByClass(UAudioComponent::StaticClass()));
	audio->Play();
}
