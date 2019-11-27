// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM()
enum class MonsterTypes : uint8 {
	/**Spider = 0,
	Ghost = 1,
	Slime = 2,
	Eye = 3*/
	Spider 	UMETA(DisplayName = "Spider"),
	Ghost 	UMETA(DisplayName = "Ghost"),
	Slime	UMETA(DisplayName = "Slime"),
	Eye		UMETA(DisplayName = "Eye")
};
