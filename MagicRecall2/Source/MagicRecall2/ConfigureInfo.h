// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterTypes.h"
#include <vector>

/**
 * 
 */
struct MAGICRECALL2_API ConfigureInfo {
	std::vector<FVector> locations; // range
	// float interval;
	int times; // how many times it spawns before a boss appears
	int nums;

	bool isBoss;
	int rounds; // set how many rounds(only for boss)
};
