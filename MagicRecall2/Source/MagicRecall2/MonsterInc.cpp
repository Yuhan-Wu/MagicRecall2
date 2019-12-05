// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterInc.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"
#include "Components/BoxComponent.h"
#include "ConstructorHelpers.h"
#include <cstdlib>
#include <string>

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
		if (total_time > max_time || total_num < max_num) {
			bool spawn_boss = true;
			for (std::pair<const MonsterTypes, FConfigureInfo> it : intervals) {
				if (intervals[it.first].nums > 0) {
					all_clear = false;
					if (total_time > max_time || total_num < max_num) {
						for (auto i = 0; i < intervals[it.first].nums; i++) {
							Spawn(it.first," ");
							// UE_LOG(LogTemp, Log, TEXT("Spawn"));
						}
						intervals[it.first].nums = 0;
						--intervals[it.first].times;
					}
				}
				if (intervals[it.first].times > 0) {
					spawn_boss = false;
				}
			}
			if (spawn_boss) {
				for (auto i = 0; i < Monsters[bossType].nums; i++) {
					UE_LOG(LogTemp, Log, TEXT("Boss"));
					SpawnBoss(bossType);
				}
				for (std::pair<const MonsterTypes, FConfigureInfo> it : intervals) {
					// intervals[it.first].nums = Monsters[it.first].nums;
					intervals[it.first].times = Monsters[it.first].times;
				}
				max_num += 2;
				max_time -= 2;
				rounds--;
			}
			if (all_clear) {
				bool change_all = true;
				for (std::pair<const MonsterTypes, FConfigureInfo> it : intervals) {
					if (intervals[it.first].times > 0) {
						intervals[it.first].nums = Monsters[it.first].nums;
						change_all = false;
					}
				}
				if (change_all) {
					for (std::pair<const MonsterTypes, FConfigureInfo> it : intervals) {
						intervals[it.first].nums = Monsters[it.first].nums;
					}
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
	total_num_of_monsters += temp * rounds;
	for (FConfigureInfo it : twitch_configures) {
		// no boss for twitch
		twitch_intervals[it.type] = FConfigureInfo(it);
		twitch_Monsters[it.type] = FConfigureInfo(it);
		//removed twitch monsters adding to monster count - not sure what intended behavior was
		//total_num_of_monsters += it.nums * it.times;
	}
}

void AMonsterInc::Spawn(MonsterTypes type, bool isBoss, FName userName) {
	total_num += 1;
	total_time = 0;
	int random_loc = rand() % boxes.Num();
	FVector location = FMath::RandPointInBox(boxes[random_loc]->GetCollisionComponent()->Bounds.GetBox());
	location.Z = boxes[random_loc]->GetCollisionComponent()->Bounds.GetBox().GetCenter().Z;

	switch (type)
	{
	case MonsterTypes::Spider:
	{
		UE_LOG(LogTemp, Log, TEXT("Spider"));
		AEnemySpider* enemy= static_cast<AEnemySpider*>(GetWorld()->SpawnActor(BP_Spider, &location));
		if (AEnemySpider::Spider_Num == 0) {
			enemy->PlaySound();
		}
		AEnemySpider::Spider_Num++;
		if (isBoss) {
			enemy->setHealthAndShowHealthBar(3);
		}
		enemy->user_name = userName;
		break;
	}
	case MonsterTypes::Eye:
	{
		UE_LOG(LogTemp, Log, TEXT("Eye"));
		if (userName != "") {
			UE_LOG(LogTemp, Log, TEXT("Twitch"));
		}
		AEnemyEye* enemy = static_cast<AEnemyEye*>(GetWorld()->SpawnActor(BP_Eye, &location));
		if (AEnemyEye::Eye_Num == 0) {
			enemy->PlaySound();
		}
		AEnemyEye::Eye_Num++;
		if (isBoss) {
			enemy->setHealthAndShowHealthBar(3);
		}
		enemy->user_name = userName;

		break;
	}
	case MonsterTypes::Ghost:
	{
		UE_LOG(LogTemp, Log, TEXT("Ghost"));
		int rot = 0;
		switch (random_loc) {
		case 0:
			rot = 90;
			break;
		case 1:
			rot = 270;
			break;
		case 2:
			rot = 180;
			break;
		case 3:
			rot = 0;
			break;
		}
		FRotator rot1 = FRotator(0, rot, 0);
		// FQuat QuatRotation1 = FQuat(rot1);
		AEnemyGhost* enemy = static_cast<AEnemyGhost*>(GetWorld()->SpawnActor(BP_Ghost, &location));
		enemy->SetActorRotation(rot1);
		// enemy1->AddActorLocalRotation(QuatRotation1);
		if (AEnemyGhost::Ghost_Num == 0) {
			enemy->PlaySound();
		}
		AEnemyGhost::Ghost_Num++;
		/*
		FRotator rot2 = FRotator(0, -45, 0);
		FQuat QuatRotation2 = FQuat(rot2);
		AEnemyGhost* enemy2 = static_cast<AEnemyGhost*>(GetWorld()->SpawnActor(BP_Ghost, &location));
		enemy2->AddActorLocalRotation(QuatRotation2);
		*/
		if (isBoss) {
			enemy->setHealthAndShowHealthBar(3);
		}
		enemy->user_name = userName;
		break;
	}
	case MonsterTypes::Slime:
	{
		UE_LOG(LogTemp, Log, TEXT("Slime"));
		// FQuat QuatRotation1 = FQuat(rot1);
		if (BP_Slime == NULL) {
			UE_LOG(LogTemp, Log, TEXT("BAD INITIALIZATION"));
		}
		AEnemySlime* enemy = static_cast<AEnemySlime*>(GetWorld()->SpawnActor(BP_Slime, &location));
		// enemy1->AddActorLocalRotation(QuatRotation1);
		if (AEnemySlime::Slime_Num == 0) {
			enemy->PlaySound();
		}
		AEnemySlime::Slime_Num++;
		if (isBoss) {
			enemy->setHealthAndShowHealthBar(3);
		}
		enemy->user_name = userName;
		break;
	}
	default:
		UE_LOG(LogTemp, Log, TEXT("no spawn"));
		break;
	}
}

void AMonsterInc::SpawnBoss(MonsterTypes type){
	Spawn(type, true," ");
}

void AMonsterInc::Spawn(MonsterTypes type,FName name)
{
	Spawn(type, false, name);
}

void AMonsterInc::MonsterNumDecrease() {
	if (total_num > 0) total_num--;
	if(total_num_of_monsters>0) total_num_of_monsters--;
}

void AMonsterInc::ReceiveTwitchInput(FString input,FName name) {
	// UE_LOG(LogTemp, Log, TEXT("Spawn"));
	MonsterTypes type = enum_map[input.ToUpper()];
	// if (total_num < max_num) {
	// UE_LOG(LogTemp, Log, TEXT("Name is %s"),*(name.ToString()));
		while (twitch_intervals[type].nums > 0) {
			Spawn(type,name);
			twitch_intervals[type].nums--;
		}
		twitch_intervals[type].times--;
		if (twitch_intervals[type].times > 0) {
			twitch_intervals[type].nums = twitch_Monsters[type].nums;
		}
	// }
}
