// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "UObject/Interface.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include <mutex>
#include "Enemy.generated.h"


extern std::mutex mtx;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemy : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MAGICRECALL2_API IEnemy
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	int health = 1;
	bool showHealthBar = false;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemyInterface")
		void move();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemyInterface")
		void receiveDamage();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemyInterface")
		void attack();

	void setMoveTarget(AActor * i_moveTarget) { moveTarget = i_moveTarget; }
	AActor * const getMoveTarget() { return moveTarget; }

	void setAttackTarget(AActor * i_attackTarget) { attackTarget = i_attackTarget; }
	AActor * const getAttackTarget() { return attackTarget; }

	void setHealthAndShowHealthBar(int new_health) {
		health = new_health;
		showHealthBar = true;
	}

private:
	AActor * moveTarget;
	AActor * attackTarget;
};