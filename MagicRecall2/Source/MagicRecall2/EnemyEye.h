// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Enemy.h"
#include "EnemyEye.generated.h"

UCLASS()
class MAGICRECALL2_API AEnemyEye : public ACharacter, public IEnemy
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyEye();

protected:
	float Speed = 400;
	UProjectileMovementComponent* ProjectileMovementComponent;
	float i = 0.0f;
	float AngleAxis = 0;

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

	virtual void Tick(float DeltaSeconds) override;

};
