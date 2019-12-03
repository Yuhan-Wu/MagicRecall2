// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterTypes.h"

#include "CoreMinimal.h"
#include <vector>
#include "ConfigureInfo.generated.h"

/**
 * 
 */
USTRUCT()
struct FConfigureInfo {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = DisplayInfo)
	MonsterTypes type;

	// float interval;
	UPROPERTY(EditAnywhere, Category = DisplayInfo)
	int8 times; // how many times it spawns before a boss appears
	UPROPERTY(EditAnywhere, Category = DisplayInfo)
	int8 nums;

	UPROPERTY(EditAnywhere, Category = DisplayInfo)
	bool isBoss;
	UPROPERTY(EditAnywhere, Category = DisplayInfo)
	int8 rounds; // set how many rounds(only for boss)

	FConfigureInfo() {
		type = MonsterTypes::Eye;
		times = 0;
		nums = 0;
		isBoss = false;
		rounds = 0;
	}

	FConfigureInfo(const FConfigureInfo& other) {
		type = other.type;
		times = other.times;
		nums = other.nums;
		isBoss = other.isBoss;
		rounds = other.rounds;
	}
};