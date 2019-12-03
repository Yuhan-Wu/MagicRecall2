// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystemComponent.h"

#include "Components/AudioComponent.h"

#include <vector>
#include "MagicRecall2Character.generated.h"

UCLASS(config=Game)
class AMagicRecall2Character : public ACharacter
{
	GENERATED_BODY()
public:
	AMagicRecall2Character();

	virtual void BeginPlay() override;

	virtual void Tick(float) override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	// Offset from player to where fireballs are shot
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UAudioComponent* AudioComponent;

	// Fireballs
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AFireBall> Fireballs;

	UFUNCTION(BlueprintCallable) FORCEINLINE
		bool GetAttackingState() { return bAttacking; }

	UFUNCTION(BlueprintCallable) FORCEINLINE
		bool GetHittingState() { return block_attack; }

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	// Mahou timer
	FTimerHandle MahouTimer;

	// Mahou direction
	std::vector<float> Angles{ 0 , -60, 60, -90, 90};

	// Power up
	//Base level, 1 bonfire, 2 bonfire, 3 bonfire
	std::vector<float> DistanceLevel{600,600,1000,1200};
	std::vector<float> SpeedLevel{600,600,1400,1800};
	std::vector<float> FireballLevel{ 1,3,3,5 };
	int level=0;
	int numOfFireballs = 3;
	float cosValue = 0.5f;

	FTimerHandle handler;

	UParticleSystemComponent* particles;

	float shield_timer;

public:

	// Magic Recall functions
	void MahouCast();
	void MahouCastOff();
	void Mahou();

	UFUNCTION()
	void ShieldDisappear();

	// Functions related to power-ups
	int PowerUp();
	int BackToMuggle();

	UFUNCTION()
	void TakeDamage(int damage);

	bool bAttacking;

	bool block_attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int hp;

};

