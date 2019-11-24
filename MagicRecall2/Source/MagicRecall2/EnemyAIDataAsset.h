// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EnemyAIDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class MAGICRECALL2_API UEnemyAIDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	UBehaviorTree* BehaviorTree;
};
