// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Enemy.generated.h"



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
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemyInterface")
		void move();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemyInterface")
		void receiveDamage();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemyInterface")
		void attack();

	void setMoveTarget(UCharacterMovementComponent * i_moveTarget) { moveTarget = i_moveTarget; }
	UCharacterMovementComponent * const getMoveTarget() { return moveTarget; }

	void setAttackTarget(UCharacterMovementComponent * i_attackTarget) { attackTarget = i_attackTarget; }
	UCharacterMovementComponent * const getAttackTarget() { return attackTarget; }

private:
	UCharacterMovementComponent * moveTarget;
	UCharacterMovementComponent * attackTarget;
};
