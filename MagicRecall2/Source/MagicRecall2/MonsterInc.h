// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <map>
#include "GameFramework/Actor.h"
#include "ConfigureInfo.h"
#include "MonsterTypes.h"
#include "MonsterInc.generated.h"

UCLASS()
class MAGICRECALL2_API AMonsterInc : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonsterInc();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Spawn(MonsterTypes);

	std::map<MonsterTypes,ConfigureInfo> Monsters;
	std::map<MonsterTypes, ConfigureInfo> intervals;
	float total_time;
	int rounds;
	MonsterTypes bossType;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Configure(std::map<MonsterTypes, ConfigureInfo>);
};
