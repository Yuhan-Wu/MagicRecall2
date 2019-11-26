// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <map>
#include "GameFramework/Actor.h"
#include "ConfigureInfo.h"
#include "MonsterTypes.h"
#include "EnemySpider.h"
#include "MonsterInc.generated.h"

UCLASS()
class MAGICRECALL2_API AMonsterInc : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonsterInc();

	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<AEnemySpider> BP_Spider;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Spawn(MonsterTypes);

	std::map<MonsterTypes,ConfigureInfo> Monsters;
	std::map<MonsterTypes, ConfigureInfo> intervals;
	int rounds;
	MonsterTypes bossType;

	//how long since last monster spawns
	float total_time;
	//how many monsters on the map
	int total_num;

	float max_time = 10;
	int max_num = 10;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Configure(std::map<MonsterTypes, ConfigureInfo>);

	UFUNCTION()
	void MonsterNumDecrease();
};