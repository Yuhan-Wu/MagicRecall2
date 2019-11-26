// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterInc.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"
#include "Components/BoxComponent.h"
#include "ConstructorHelpers.h"
#include <cstdlib>

// Sets default values
AMonsterInc::AMonsterInc()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	total_time = 0;
	total_num = 0;

	static ConstructorHelpers::FObjectFinder<UClass> SpiderBPFinder(TEXT("Blueprint'/Game/Blueprints/Enemies/BP_Spider.BP_Spider_C'"));
	BP_Spider= SpiderBPFinder.Object;

}

// Called when the game starts or when spawned
void AMonsterInc::BeginPlay()
{
	Super::BeginPlay();

	//FVector test_loc(-900, -600, 230);
	//UE_LOG(LogTemp, Log, TEXT("Spawn"));
	//AEnemySpider* enemy = static_cast<AEnemySpider*>(GetWorld()->SpawnActor(BP_Spider, &test_loc));
	
}

// Called every frame
void AMonsterInc::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime); 
	bool spawn_boss = false;
	do {
		bool all_clear = true;
		if (total_time < max_time || total_num < max_num) {
			spawn_boss = true;
			for (std::pair<const MonsterTypes, ConfigureInfo> it : intervals) {
				if (intervals[it.first].nums != 0) {
					all_clear = false;
					spawn_boss = false;
					for (auto i = 0; i < intervals[it.first].nums; i++) {
						Spawn(it.first);
					}
					intervals[it.first].nums = 0;
					if (--intervals[it.first].times != 0) {
						spawn_boss = false;
					}
				}
			}
			if (spawn_boss) {
				for (auto i = 0; i < intervals[bossType].nums;i++) {
					Spawn(bossType);
				}
				for (std::pair<const MonsterTypes, ConfigureInfo> it : intervals) {
					intervals[it.first].times = Monsters[it.first].times;
				}
				max_num += 2;
				max_time -= 2;
			}
			if (all_clear) {
				for (std::pair<const MonsterTypes, ConfigureInfo> it : intervals) {
					intervals[it.first].nums = Monsters[it.first].nums;
				}
			}
		}
		else {
			total_time += DeltaTime;
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
	total_num += 1;
	total_time = 0;
	switch (type)
	{
	case MonsterTypes::Spider:
	{
		std::vector<FVector> locations = Monsters[MonsterTypes::Spider].locations;
		int random_loc = rand() % NUM_OF_POSITIONS;
		FVector location = FMath::RandPointInBox(boxes[random_loc]->GetCollisionComponent()->Bounds.GetBox());
		//TODO: probably need to store the pointer
		AEnemySpider* enemy= static_cast<AEnemySpider*>(GetWorld()->SpawnActor(BP_Spider, &locations[random_loc]));
		break;
	}
		//TODO add other monsters
	default:
		break;
	}
}

void AMonsterInc::MonsterNumDecrease() {
	total_num--;
}
