// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MagicRecall2Character.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Bonfire.generated.h"

UCLASS(BlueprintType)
class MAGICRECALL2_API ABonfire : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABonfire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool isLit = false;

	UParticleSystemComponent* particles;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	UBoxComponent* CollisionComponent;

	UFUNCTION(BlueprintCallable)
	void ReceiveTwitchInput(AMagicRecall2Character* player,FName userName);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName user_name;

};
