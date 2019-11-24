// Fill out your copyright notice in the Description page of Project Settings.


#include "ConfigureInfo.h"
#include "MonsterTypes.h"
#include <vector>

struct ConfigureInfo {
	std::vector<FVector> locations;
	float interval;

	bool isBoss;
	int rounds;//set how many rounds(only for boss)
};