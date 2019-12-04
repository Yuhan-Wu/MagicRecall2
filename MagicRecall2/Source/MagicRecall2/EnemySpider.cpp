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
#include "MagicRecall2Character.h"
#include <Runtime/Engine/Classes/Engine/Engine.h>

int AEnemySpider::Spider_Num = 0;

// Sets default values
AEnemySpider::AEnemySpider()
{

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
	mtx.lock();
	for (TActorIterator<AMonsterInc> It(GetWorld()); It; ++It)
	{
		It->MonsterNumDecrease();
		break;
	}
	Spider_Num--;
	mtx.unlock();
	Destroy();
}

void AEnemySpider::attack_Implementation()
{
	m_bAttacking = true;
	UE_LOG(LogTemp, Log, TEXT("%s is attacking %s"), *GetName(), *getAttackTarget()->GetName());
	// UE_LOG(LogTemp, Log, TEXT("%s is attacking %s"), *GetName(), *getAttackTarget()->GetName());
	for (TActorIterator<AMagicRecall2Character> wizard(GetWorld()); wizard; ++wizard)
	{
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		if (wizard) {
			if (!wizard->block_attack) {
				wizard->TakeDamage(1);
			}
		}
		break;
	}
}

void AEnemySpider::PlaySound() {
	UAudioComponent* audio = Cast<UAudioComponent>(GetComponentByClass(UAudioComponent::StaticClass()));
	audio->Play();
}
