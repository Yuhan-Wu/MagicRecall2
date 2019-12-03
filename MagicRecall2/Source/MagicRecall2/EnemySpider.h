// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.h"
#include "EnemySpider.generated.h"

UCLASS()
class MAGICRECALL2_API AEnemySpider : public ACharacter, public IEnemy
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemySpider();

protected:

public:	

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemyInterface")
		void move();
		virtual void move_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemyInterface")
		void receiveDamage();
		virtual void receiveDamage_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemyInterface")
		void attack();
		virtual void attack_Implementation() override;

	UFUNCTION(BlueprintCallable) FORCEINLINE
		bool GetAttackingState() {return m_bAttacking;}

private:
	bool m_bAttacking;
};
