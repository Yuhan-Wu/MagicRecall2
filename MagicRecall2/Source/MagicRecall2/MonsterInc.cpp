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
	fire_function = 0;
	total_num_of_monsters = 0;

	static ConstructorHelpers::FObjectFinder<UClass> SpiderBPFinder(TEXT("Blueprint'/Game/Blueprints/Enemies/BP_Spider.BP_Spider_C'"));
	BP_Spider= SpiderBPFinder.Object;

	enum_map["SPIDER"] = MonsterTypes::Spider;
	// TODO: need to add other types of monsters
}

// Called when the game starts or when spawned
void AMonsterInc::BeginPlay()
{
	Super::BeginPlay();

	//FVector test_loc(-900, -600, 230);
	//UE_LOG(LogTemp, Log, TEXT("Spawn"));
	//AEnemySpider* enemy = static_cast<AEnemySpider*>(GetWorld()->SpawnActor(BP_Spider, &test_loc));
	Configure();
}

// Called every frame
void AMonsterInc::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	fire_function += DeltaTime;
	if (fire_function > 10) {
		fire_function = 0;
		if (rounds > 0) {
			bool all_clear = true;
			if (total_time > max_time || total_num < max_num) {
				bool spawn_boss = true;
				for (std::pair<const MonsterTypes, FConfigureInfo> it : intervals) {
					if (intervals[it.first].nums != 0) {
						all_clear = false;
						spawn_boss = false;
						for (auto i = 0; i < intervals[it.first].nums; i++) {
							Spawn(it.first);
							// UE_LOG(LogTemp, Log, TEXT("Spawn"));
						}
						intervals[it.first].nums = 0;
						if (--intervals[it.first].times != 0) {
							spawn_boss = false;
						}
					}
				}
				if (spawn_boss) {
					for (auto i = 0; i < intervals[bossType].nums; i++) {
						Spawn(bossType);
						// UE_LOG(LogTemp, Log, TEXT("Spawn"));
					}
					for (std::pair<const MonsterTypes, FConfigureInfo> it : intervals) {
						intervals[it.first].times = Monsters[it.first].times;
					}
					max_num += 2;
					max_time -= 2;
					rounds--;
				}
				if (all_clear) {
					for (std::pair<const MonsterTypes, FConfigureInfo> it : intervals) {
						intervals[it.first].nums = Monsters[it.first].nums;
					}
				}
			}
			else {
				total_time += DeltaTime;
			}
		}
	}

}

void AMonsterInc::Configure() {
	for (FConfigureInfo it:configures) {
		if (it.isBoss) {
			bossType = it.type;
			rounds = it.rounds;
			total_num_of_monsters += it.nums * it.rounds;
			break;
		}
		intervals[it.type] = it;
		Monsters[it.type] = it;
		total_num_of_monsters += it.nums * it.times;
	}
	for (FConfigureInfo it : twitch_configures) {
		if (it.isBoss) {
			bossType = it.type;
			rounds = it.rounds;
			total_num_of_monsters += it.nums * it.rounds;
			break;
		}
		twitch_intervals[it.type] = it;
		twitch_Monsters[it.type] = it;
		total_num_of_monsters += it.nums * it.times;
	}
}

void AMonsterInc::Spawn(MonsterTypes type) {
	total_num += 1;
	total_time = 0;
	switch (type)
	{
	case MonsterTypes::Spider:
	{
		UE_LOG(LogTemp, Log, TEXT("Spider"));
		// std::vector<FVector> locations = Monsters[MonsterTypes::Spider].locations;
		int random_loc = rand() % boxes.Num();
		FVector location = FMath::RandPointInBox(boxes[random_loc]->GetCollisionComponent()->Bounds.GetBox());
		//TODO: probably need to store the pointer
		AEnemySpider* enemy= static_cast<AEnemySpider*>(GetWorld()->SpawnActor(BP_Spider, &location));
		
		break;
	}
		//TODO add other monsters
	default:
		break;
	}
}

//TODO: PLEASE CALL THIS FUNCTION BEFORE MONSTER DIES
void AMonsterInc::MonsterNumDecrease() {
	total_num--;
}

//TODO: need to create a new interval map for twitch
void AMonsterInc::ReceiveTwitchInput(FString input) {
	// UE_LOG(LogTemp, Log, TEXT("Spawn"));
	MonsterTypes type = enum_map[input.ToUpper()];
	bool spawn_boss = true;
	bool all_clear = true;
	if (total_num < max_num) {
		if (twitch_intervals[type].nums != 0) {
			Spawn(type);
			twitch_intervals[type].nums = 0;
			--twitch_intervals[type].times;
		}
		for (std::pair<MonsterTypes, FConfigureInfo> item : twitch_intervals) {
			if (item.second.nums == 0) {
				if (item.second.times == 0) {
					spawn_boss = false;
				}
				else {
					twitch_intervals[item.first].nums = twitch_Monsters[item.first].nums;
					twitch_intervals[item.first].times--;
				}
			}
			else {
				all_clear = false;
			}
		}
		if (spawn_boss) {
			for (auto i = 0; i < twitch_intervals[bossType].nums; i++) {
				Spawn(bossType);
			}
			for (std::pair<const MonsterTypes, FConfigureInfo> it : twitch_intervals) {
				twitch_intervals[it.first].times = twitch_Monsters[it.first].times;
			}
			max_num += 2;
			max_time -= 2;
		}
		if (all_clear) {
			for (std::pair<const MonsterTypes, FConfigureInfo> it : twitch_intervals) {
				twitch_intervals[it.first].nums = twitch_Monsters[it.first].nums;
			}
		}
	}
}
