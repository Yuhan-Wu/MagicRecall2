// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_UpdateView.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "AIController.h"
#include "EnemyAIController.h"
#include "Enemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

void UBTS_UpdateView::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	AActor* enemy = Cast<AAIController>(OwnerComp.GetOwner())->GetPawn();
	check(enemy);
	AActor* targetActor = Cast<IEnemy>(enemy)->getAttackTarget();
	OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(FName("target"), targetActor);
	if (enemy) {
		FHitResult hitResult = FHitResult(EForceInit::ForceInit);
		FCollisionQueryParams TraceParams(FName("Ignore Self"), false, enemy);
		GetWorld()->LineTraceSingleByChannel(hitResult, enemy->GetActorLocation(), targetActor->GetActorLocation(), ECC_Pawn, TraceParams);
		OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(FName("bHasLineOfSight"), hitResult.GetActor() == targetActor);
	}
}