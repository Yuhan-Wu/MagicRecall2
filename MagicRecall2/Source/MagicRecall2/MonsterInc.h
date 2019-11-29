// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <map>
#include "GameFramework/Actor.h"
#include "Engine/TriggerBox.h"
#include "ConfigureInfo.h"
#include "MonsterTypes.h"
#include "EnemySpider.h"
#include "MonsterInc.generated.h"

UCLASS(BlueprintType)
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

	std::map<MonsterTypes,FConfigureInfo> Monsters;
	std::map<MonsterTypes, FConfigureInfo> twitch_Monsters;

	float max_time = 10;
	int max_num = 2;

	std::map<MonsterTypes, FConfigureInfo> intervals;
	std::map<MonsterTypes, FConfigureInfo> twitch_intervals;
	int rounds;
	MonsterTypes bossType;

	//how long since last monster spawns
	float total_time;
	float fire_function;
	//how many monsters on the map
	int total_num;

	//UPROPERTY(EditAnywhere, Category = Gameplay)
	//FVector Position_List[NUM_OF_POSITIONS];
	
	UPROPERTY(EditAnywhere)
	TArray<ATriggerBox *> boxes;

	UPROPERTY(EditAnywhere)
	TArray<struct FConfigureInfo> configures;

	UPROPERTY(EditAnywhere)
	TArray<struct FConfigureInfo> twitch_configures;

	void Configure();

	std::map<FString, MonsterTypes> enum_map;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void MonsterNumDecrease();

	UFUNCTION(BlueprintCallable)
	void ReceiveTwitchInput(FString input);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int total_num_of_monsters;
};