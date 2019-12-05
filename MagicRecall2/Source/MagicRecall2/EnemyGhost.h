// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.h"
#include "ProjectileGhost.h"
#include "Components/AudioComponent.h"
#include "EnemyGhost.generated.h"

UCLASS()
class MAGICRECALL2_API AEnemyGhost : public APawn, public IEnemy
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyGhost();

protected:
	FTimerHandle handler;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AProjectileGhost> Projectile;
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

	virtual void BeginPlay() override;

	static int Ghost_Num;

	float timeUntilCanFlip = 10.0f;

	void PlaySound();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName user_name;
};
