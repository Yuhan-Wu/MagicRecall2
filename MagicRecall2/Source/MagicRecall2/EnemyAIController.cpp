// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Enemy.h"
#include "ConstructorHelpers.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

AEnemyAIController::AEnemyAIController() {
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTree(TEXT("BehaviorTree'/Game/Blueprints/BehaviorTree/BT_Enemy.BT_Enemy'"));
	if (BehaviorTree.Succeeded()) { m_pEnemyBehaviorTree = BehaviorTree.Object; }
	UE_LOG(LogTemp, Warning, TEXT("%d"), BehaviorTree.Succeeded());
}

void AEnemyAIController::BeginPlay() {
	AActor* player = GetWorld()->GetFirstPlayerController()->GetPawn();
	IEnemy* enemy = Cast<IEnemy>(GetPawn());
	if (!ensure(enemy)) { return; }
	enemy->setAttackTarget(player);
	enemy->setMoveTarget(player);
	if (!ensure(m_pEnemyBehaviorTree)) { return; }
	GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(FName("target"), player);
}

void AEnemyAIController::Tick(float i_DeltaTime) {
	AActor* player = GetWorld()->GetFirstPlayerController()->GetPawn();
	IEnemy* enemy = Cast<IEnemy>(GetPawn());
	if (!ensure(enemy)) { return; }
	FHitResult hitResult = FHitResult(EForceInit::ForceInit);
	GetWorld()->LineTraceSingleByChannel(hitResult, GetPawn()->GetActorLocation(), player->GetActorLocation(), ECC_Visibility);
	GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(FName("bHasLineOfSight"), hitResult.GetActor() != nullptr);
}

void AEnemyAIController::OnPossess(APawn* i_pInPawn) {
	RunBehaviorTree(m_pEnemyBehaviorTree);
}