// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Controller.h"
#include "Enemy.h"
#include "ConstructorHelpers.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

AEnemyAIController::AEnemyAIController() {
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AEnemyAIController::BeginPlay() {
	Super::BeginPlay();
	AActor* player = GetWorld()->GetFirstPlayerController()->GetPawn();
	IEnemy* enemy = Cast<IEnemy>(GetPawn());
	enemy->setAttackTarget(player);
	enemy->setMoveTarget(player);
}

void AEnemyAIController::Tick(float i_DeltaTime) {
	Super::Tick(i_DeltaTime);
}

void AEnemyAIController::OnPossess(APawn* i_pInPawn) {
	Super::OnPossess(i_pInPawn);
	RunBehaviorTree(EnemyBehaviorTree);
}