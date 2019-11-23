// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class MAGICRECALL2_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	virtual void BeginPlay() override;
	virtual void Tick(float i_DeltaTime) override;
	virtual void OnPossess(APawn* i_pInPawn) override;

public:
	AEnemyAIController();
	UPROPERTY(EditAnywhere, Category = AI)
		UBehaviorTree* EnemyBehaviorTree;
};
