// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
#include "MagicRecall2Character.h"
#include <vector>
#include <mutex>
#include "Engine.h"
#include "FireBall.h"
#include "Enemy.h"
#include "EnemySlime.h"
#include "EnemyGhost.h"
#include "EnemySpider.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

//////////////////////////////////////////////////////////////////////////
// AMagicRecall2Character
std::mutex mtx;

AMagicRecall2Character::AMagicRecall2Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	block_attack = false;

	shield_timer = 0;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));

	hp = 2;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void AMagicRecall2Character::BeginPlay() {
	Super::BeginPlay();
	particles = Cast<UParticleSystemComponent>(GetComponentByClass(UParticleSystemComponent::StaticClass()));
	particles->DeactivateSystem();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMagicRecall2Character::OnOverlap);
}

void AMagicRecall2Character::Tick(float delta) {
	Super::Tick(delta);
	if (block_attack) {
		shield_timer += delta;
		if (shield_timer > 2) {
			ShieldDisappear();
			shield_timer = 0;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMagicRecall2Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMagicRecall2Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMagicRecall2Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMagicRecall2Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMagicRecall2Character::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AMagicRecall2Character::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AMagicRecall2Character::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AMagicRecall2Character::OnResetVR);

	// Shoot fire balls
	PlayerInputComponent->BindAction("Mahou", IE_Pressed, this, &AMagicRecall2Character::MahouCast);
	PlayerInputComponent->BindAction("Mahou", IE_Released, this, &AMagicRecall2Character::MahouCastOff);
}


void AMagicRecall2Character::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AMagicRecall2Character::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AMagicRecall2Character::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AMagicRecall2Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMagicRecall2Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMagicRecall2Character::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMagicRecall2Character::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

/**
*Magic Recall functions
*/

// Shoot (...) fire balls
void AMagicRecall2Character::MahouCast() {
	// shoot every 0.5 second
	// GetWorld()->GetTimerManager().SetTimer(MahouTimer,this,&AMagicRecall2Character::Mahou,1.5f,true,1.5f);
	Mahou();
}

void AMagicRecall2Character::MahouCastOff() {
	GetWorld()->GetTimerManager().ClearTimer(MahouTimer);
	bAttacking = false;
}

void AMagicRecall2Character::Mahou() {
	// Play animation, sound, whatever :)
	if (Fireballs)
	{
		bAttacking = true;
		AudioComponent->Play();
		UE_LOG(LogTemp, Log, TEXT("Fireball_success"));
		// Get location & rotation
		FVector WizardLocation;
		FRotator WizardRotation;
		GetActorEyesViewPoint(WizardLocation, WizardRotation);
		WizardRotation=GetArrowComponent()->GetComponentRotation();
		
		// To world location
		FVector MuzzleLocation = WizardLocation + FTransform(WizardRotation).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = WizardRotation;
		// Raise aiming point
		MuzzleRotation.Pitch += 30.0f;
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			
			for (auto i = 0; i < numOfFireballs; i++) {
				AFireBall* Projectile = World->SpawnActor< AFireBall >(Fireballs, MuzzleLocation, MuzzleRotation, SpawnParams);
				Projectile->SetDistance(DistanceLevel[level]);
				Projectile->SetSpeed(SpeedLevel[level]);
				if (Projectile)
				{
					// Track
					FVector LaunchDirection = MuzzleRotation.Vector();
					LaunchDirection = FVector(LaunchDirection.X, LaunchDirection.Y, 0);
					LaunchDirection=LaunchDirection.RotateAngleAxis(Angles[i], FVector::UpVector);
					Projectile->MahouInDirection(LaunchDirection);
					Projectile->SetHome(this);
					
					// UE_LOG(LogTemp, Log, TEXT("Born"));
				}
			}
			AudioComponent->Play();
		}
	}

}

int AMagicRecall2Character::PowerUp() {
	if (level < DistanceLevel.size()) {
		level++;
	}
	return level;
}

int AMagicRecall2Character::BackToMuggle() {
	// UE_LOG(LogTemp, Log, TEXT("decrease"));
	if (level > 0) {
		level--;
	}
	return level;
}

void AMagicRecall2Character::TakeDamage(int damage) {
	mtx.lock();
	if (!block_attack) {
		hp -= damage;
		if (hp <= 0) {
			// TODO: die
			FLatentActionInfo LatentInfo;
			UGameplayStatics::OpenLevel(this, FName("GameOver"));
		}
		else {
			block_attack = true;
			UE_LOG(LogTemp, Log, TEXT("shield on"));
			particles->ActivateSystem();
			// GetWorld()->GetTimerManager().SetTimer(handler, this, &AMagicRecall2Character::ShieldDisappear, 1, false);
			// TODO: probably also need to remove timer???
			// TODO: remove collision with the fireballs
		}
	}
	mtx.unlock();
 }

void AMagicRecall2Character::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	UE_LOG(LogTemp, Log, TEXT("yup"));
	if (OtherActor != this && Cast<IEnemy>(OtherActor)) {
		if (!Cast<AEnemySlime>(OtherActor) && !Cast<AEnemyGhost>(OtherActor) && !Cast<AEnemySpider>(OtherActor)) {
			// UE_LOG(LogTemp, Log, TEXT("yup"));
			TakeDamage(1);
			OtherActor->Destroy();
		}
	}
}

void AMagicRecall2Character::ShieldDisappear() {
	UE_LOG(LogTemp, Log, TEXT("remove"));
	mtx.lock();
	block_attack = false;
	particles->DeactivateSystem();
	// GetWorld()->GetTimerManager().ClearTimer(handler);
	mtx.unlock();
}
