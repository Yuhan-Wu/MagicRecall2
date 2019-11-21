// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void AEnemyAIController::Tick(float i_DeltaSecond) 
{
	auto player = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!ensure(player)) { return; }
	MoveToActor(player, 1.0f);

}