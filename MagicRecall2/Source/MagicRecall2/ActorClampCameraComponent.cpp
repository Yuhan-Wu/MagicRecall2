// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorClampCameraComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/LocalPlayer.h"
#include "SceneView.h"

// Sets default values for this component's properties
UActorClampCameraComponent::UActorClampCameraComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UActorClampCameraComponent::BeginPlay()
{
	Super::BeginPlay();
	
	m_camera = GetOwner()->FindComponentByClass<UCameraComponent>();
	check(m_camera);
}


// Called every frame
void UActorClampCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector projected;
	FVector2D normalizedScreenPosition;
	bool bTargetBehindCamera = false;
	FVector playerPosition = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn()->GetActorLocation();
	FVector playerVelocity = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn()->GetVelocity();
	ULocalPlayer* localPlayer = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetLocalPlayer();
	if (localPlayer && localPlayer->ViewportClient){

		FSceneViewProjectionData projectionData;
		if (localPlayer->GetProjectionData(localPlayer->ViewportClient->Viewport, EStereoscopicPass::eSSP_FULL, projectionData)){
			const FMatrix ViewProjectionMatrix = projectionData.ComputeViewProjectionMatrix();
			const FIntRect ViewRectangle = projectionData.GetConstrainedViewRect();
			FPlane playerPositionResult = ViewProjectionMatrix.TransformFVector4(FVector4(playerPosition, 1.0f));
			if (playerPositionResult.W < 0.f) {bTargetBehindCamera = true;}
			if (playerPositionResult.W == 0.f) {playerPositionResult.W = 1.f;}
			projected = FVector(playerPositionResult.X, playerPositionResult.Y, playerPositionResult.Z) / FMath::Abs(playerPositionResult.W);
			normalizedScreenPosition = FVector2D(projected.X, projected.Y);
			if (FMath::Abs(projected.X) > ClampRate || FMath::Abs(projected.Y) > ClampRate){
				// Move Camera
				FVector cameraOffset = FVector(0.f);
				if (FMath::Abs(projected.X) > ClampRate){
					cameraOffset.Y = CameraMoveSpeed * DeltaTime * (projected.X > 0 ? 1 : -1) * (FMath::Abs(projected.X) - ClampRate);
				}
				if (FMath::Abs(projected.Y) > ClampRate){
					cameraOffset.X = CameraMoveSpeed * DeltaTime * (projected.Y > 0 ? 1 : -1) * (FMath::Abs(projected.Y) - ClampRate);
				}
				m_camera->AddWorldOffset(cameraOffset);
			}
		}	
	}
}

