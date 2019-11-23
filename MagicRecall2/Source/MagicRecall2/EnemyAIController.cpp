// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Enemy.h"

AEnemyAIController::AEnemyAIController() {
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyAIController::BeginPlay() {
	AActor* player = GetWorld()->GetFirstPlayerController()->GetPawn();
	IEnemy* enemy = Cast<IEnemy>(GetPawn());
	if (!ensure(enemy)) { return; }
	enemy->setAttackTarget(player);
	enemy->setMoveTarget(player);
}

void AEnemyAIController::Tick(float i_DeltaTime) {
	IEnemy* enemy = Cast<IEnemy>(GetPawn());
	if (!ensure(enemy)) { return; }
	enemy->move();
}
