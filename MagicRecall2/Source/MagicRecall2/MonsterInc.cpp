// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterInc.h"
#include "Engine/World.h"
#include "EnemySpider.h"
#include <cstdlib>

// Sets default values
AMonsterInc::AMonsterInc()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	total_time = 0;
}

// Called when the game starts or when spawned
void AMonsterInc::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonsterInc::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 
	bool spawn_boss = false;
	do {
		spawn_boss = true;
		for (std::pair<const MonsterTypes, ConfigureInfo> it : intervals) {
			if ((intervals[it.first].interval -= DeltaTime) <= 0) {
				for (auto i = 0; i < intervals[it.first].num; i++) {
					Spawn(it.first);
				}
				intervals[it.first].interval = Monsters[it.first].interval;
				if (--intervals[it.first].times != 0) {
					spawn_boss = false;
				}
				
			}
		}
		if (spawn_boss) {
			for (auto i = 0; i < intervals[bossType].num; i++) {
				Spawn(bossType);
			}
			for (std::pair<const MonsterTypes, ConfigureInfo> it : intervals) {
				intervals[it.first].times = Monsters[it.first].times;
			}
		}
	} while (rounds != 0);
}

void AMonsterInc::Configure(std::map<MonsterTypes, ConfigureInfo> configuration) {
	Monsters = std::map<MonsterTypes, ConfigureInfo>(configuration);
	intervals= std::map<MonsterTypes, ConfigureInfo>(configuration);
	for (std::pair<const MonsterTypes, ConfigureInfo> it : intervals) {
		if (intervals[it.first].isBoss) {
			bossType = it.first;
			break;
		}
	}
}

void AMonsterInc::Spawn(MonsterTypes type) {
	switch (type)
	{
	case MonsterTypes::Spider:
	{
		std::vector<FVector> locations = Monsters[MonsterTypes::Spider].locations;
		int random_loc = rand() / locations.size();
		GetWorld()->SpawnActor(AEnemySpider::StaticClass(), &(locations[random_loc]));
		break;
	}
		//TODO add other monsters
	default:
		break;
	}
}
