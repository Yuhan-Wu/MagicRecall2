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

	static ConstructorHelpers::FObjectFinder<UClass> SpiderBPFinder(TEXT("Blueprint'/Game/Blueprints/Character/BP_Spider.BP_Spider_C'"));
	BP_Spider= SpiderBPFinder.Object;

	static ConstructorHelpers::FObjectFinder<UClass> EyeBPFinder(TEXT("Blueprint'/Game/Blueprints/Character/BP_Eye.BP_Eye_C'"));
	BP_Eye = EyeBPFinder.Object;

	static ConstructorHelpers::FObjectFinder<UClass> GhostBPFinder(TEXT("Blueprint'/Game/Blueprints/Character/BP_Ghost.BP_Ghost_C'"));
	BP_Ghost = GhostBPFinder.Object;

	static ConstructorHelpers::FObjectFinder<UClass> SlimeBPFinder(TEXT("Blueprint'/Game/Blueprints/Character/BP_Slime.BP_Slime_C'"));
	BP_Slime = SlimeBPFinder.Object;

	enum_map["SPIDER"] = MonsterTypes::Spider;
	enum_map["EYE"] = MonsterTypes::Eye;
	enum_map["GHOST"] = MonsterTypes::Ghost;
	enum_map["SLIME"] = MonsterTypes::Slime;
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
	//fire_function += DeltaTime;
	//if (fire_function > 2) {
		//fire_function = 0;
		if (rounds > 0) {
			bool all_clear = true;
			if (total_time < max_time || total_num < max_num) {
				bool spawn_boss = true; //don't spawn boss
				for (std::pair<const MonsterTypes, FConfigureInfo> it : intervals) {
					//spawn_boss = true; //possibility of spawning boss
					if (intervals[it.first].times != 0) {
						all_clear = false;
						for (auto i = 0; i < intervals[it.first].nums; i++) {
							Spawn(it.first);
							// UE_LOG(LogTemp, Log, TEXT("Spawn"));
						}
						//intervals[it.first].nums = 0;
						if (--intervals[it.first].times > 0) {
							spawn_boss = false; //don't spawn boss if we want to spawn enemies again
						}
						if (!(total_time < max_time && total_num < max_num)) {
							break;
						}
					}
				}
				if (spawn_boss) {
					for (auto i = 0; i < Monsters[bossType].nums; i++) {
						UE_LOG(LogTemp, Log, TEXT("Boss"));
						Spawn(bossType);
					}
					for (std::pair<const MonsterTypes, FConfigureInfo> it : intervals) {
						intervals[it.first].nums = Monsters[it.first].nums;
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
		else {
			//TODO: next level
		}
	//}

}

void AMonsterInc::Configure() {
	int temp = 0;
	for (FConfigureInfo it:configures) {
		if (it.isBoss) {
			bossType = it.type;
			rounds = it.rounds;
			total_num_of_monsters += it.nums * it.rounds;
			//total_num_of_monsters++;
			Monsters[it.type] = it;
			continue;
		}
		intervals[it.type]=FConfigureInfo(it);
		Monsters[it.type] = FConfigureInfo(it);
		temp += it.nums * it.times;
	}
	max_num = temp;
	total_num_of_monsters += temp * rounds;
	for (FConfigureInfo it : twitch_configures) {
		//TODO: add twitch boss type
		// no boss for twitch
		twitch_intervals[it.type] = FConfigureInfo(it);
		twitch_Monsters[it.type] = FConfigureInfo(it);
		//removed twitch monsters adding to monster count - not sure what intended behavior was
		//total_num_of_monsters += it.nums * it.times;
	}
}

void AMonsterInc::Spawn(MonsterTypes type) {
	total_num += 1;
	total_time = 0;
	int random_loc = rand() % boxes.Num();
	FVector location = FMath::RandPointInBox(boxes[random_loc]->GetCollisionComponent()->Bounds.GetBox());

	switch (type)
	{
	case MonsterTypes::Spider:
	{
		UE_LOG(LogTemp, Log, TEXT("Spider"));
		//TODO: probably need to store the pointer
		AEnemySpider* enemy= static_cast<AEnemySpider*>(GetWorld()->SpawnActor(BP_Spider, &location));
		
		break;
	}
		//TODO add other monsters
	case MonsterTypes::Eye:
	{
		UE_LOG(LogTemp, Log, TEXT("Eye"));
		//TODO: probably need to store the pointer
		AEnemyEye* enemy = static_cast<AEnemyEye*>(GetWorld()->SpawnActor(BP_Eye, &location));

		break;
	}
	case MonsterTypes::Ghost:
	{
		UE_LOG(LogTemp, Log, TEXT("Ghost"));
		//TODO: probably need to store the pointer
		FRotator rot1 = FRotator(0, 180, 0);
		// FQuat QuatRotation1 = FQuat(rot1);
		AEnemyGhost* enemy1 = static_cast<AEnemyGhost*>(GetWorld()->SpawnActor(BP_Ghost, &location));
		// enemy1->AddActorLocalRotation(QuatRotation1);

		/*
		FRotator rot2 = FRotator(0, -45, 0);
		FQuat QuatRotation2 = FQuat(rot2);
		AEnemyGhost* enemy2 = static_cast<AEnemyGhost*>(GetWorld()->SpawnActor(BP_Ghost, &location));
		enemy2->AddActorLocalRotation(QuatRotation2);
		*/
		break;
	}
	case MonsterTypes::Slime:
	{
		UE_LOG(LogTemp, Log, TEXT("Slime"));
		//TODO: probably need to store the pointer
		// FQuat QuatRotation1 = FQuat(rot1);
		if (BP_Slime == NULL) {
			UE_LOG(LogTemp, Log, TEXT("BAD INITIALIZATION"));
		}
		AEnemySlime* enemy = static_cast<AEnemySlime*>(GetWorld()->SpawnActor(BP_Slime, &location));
		// enemy1->AddActorLocalRotation(QuatRotation1);

		break;
	}
	default:
		break;
	}
}

//TODO: PLEASE CALL THIS FUNCTION BEFORE MONSTER DIES
void AMonsterInc::MonsterNumDecrease() {
	if (total_num > 0) {
		total_num--;
	}
	total_num_of_monsters--;
}

//TODO: need to create a new interval map for twitch
void AMonsterInc::ReceiveTwitchInput(FString input) {
	// UE_LOG(LogTemp, Log, TEXT("Spawn"));
	MonsterTypes type = enum_map[input.ToUpper()];
	// TODO: handle too many monsters on the grid
	if (total_num < max_num) {
		while (twitch_intervals[type].nums > 0) {
			Spawn(type);
			twitch_intervals[type].nums--;
		}
		twitch_intervals[type].times--;
		if (twitch_intervals[type].times > 0) {
			
			twitch_intervals[type].nums = twitch_Monsters[type].nums;
		}
	}
}
