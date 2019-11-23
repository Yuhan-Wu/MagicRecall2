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
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTree(TEXT("BehaviorTree'/Game/Blueprints/BehaviorTree/BT_Enemy.BT_Enemy'"));
	if (BehaviorTree.Succeeded()) { m_pEnemyBehaviorTree = BehaviorTree.Object; }
	UE_LOG(LogTemp, Warning, TEXT("%d"), BehaviorTree.Succeeded());
}

void AEnemyAIController::BeginPlay() {
	Super::BeginPlay();
	AActor* player = GetWorld()->GetFirstPlayerController()->GetPawn();
	IEnemy* enemy = Cast<IEnemy>(GetPawn());
	enemy->setAttackTarget(player);
	enemy->setMoveTarget(player);
	if (!ensure(m_pEnemyBehaviorTree)) { return; }
	GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(FName("target"), player);
}

void AEnemyAIController::Tick(float i_DeltaTime) {
	Super::Tick(i_DeltaTime);
	AActor* player = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (GetPawn()) {
		FHitResult hitResult = FHitResult(EForceInit::ForceInit);
		FCollisionQueryParams TraceParams(FName("Ignore Self"), false, GetPawn());
		GetWorld()->LineTraceSingleByChannel(hitResult, GetPawn()->GetActorLocation(), player->GetActorLocation(), ECC_Pawn, TraceParams);
		if (hitResult.GetActor())
			UE_LOG(LogTemp, Log, TEXT("Hits: %s"), *hitResult.GetActor()->GetName());
		GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(FName("bHasLineOfSight"), hitResult.GetActor() == player);
	}
}

void AEnemyAIController::OnPossess(APawn* i_pInPawn) {
	Super::OnPossess(i_pInPawn);
	RunBehaviorTree(m_pEnemyBehaviorTree);
}