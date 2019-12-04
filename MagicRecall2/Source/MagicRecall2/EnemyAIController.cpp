// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Engine/World.h"
#include "Math/Vector.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Controller.h"
#include "Enemy.h"
#include "ConstructorHelpers.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "EngineUtils.h"

AEnemyAIController::AEnemyAIController() {
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AEnemyAIController::BeginPlay() {
	Super::BeginPlay();
}

void AEnemyAIController::Tick(float i_DeltaTime) {
	Super::Tick(i_DeltaTime);
}

void AEnemyAIController::OnPossess(APawn* i_pInPawn) {
	Super::OnPossess(i_pInPawn);
	AActor* targetActor = nullptr;
	float closestActorDistance = MAX_FLT;
	for (TActorIterator<AActor> It(GetWorld(), chasingEnemyType); It; ++It)
	{
		FVector::Dist(i_pInPawn->GetActorLocation(), It->GetActorLocation());
		if (FVector::Dist(i_pInPawn->GetActorLocation(), It->GetActorLocation()) < closestActorDistance) {
			targetActor = *It;
			closestActorDistance = FVector::Dist(i_pInPawn->GetActorLocation(), It->GetActorLocation());
		}
	}
	check(targetActor);
	IEnemy* enemy = Cast<IEnemy>(i_pInPawn);
	if (!GetPawn()) UE_LOG(LogTemp, Warning, TEXT("NULLLLLLLL"));
	enemy->setAttackTarget(targetActor);
	enemy->setMoveTarget(targetActor);
	RunBehaviorTree(EnemyBehaviorTree);
}