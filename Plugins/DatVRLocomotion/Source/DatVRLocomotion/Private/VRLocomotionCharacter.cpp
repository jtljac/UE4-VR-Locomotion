// Fill out your copyright notice in the Description page of Project Settings.


#include "VRLocomotionCharacter.h"
#include "IXRTrackingSystem.h"
#include "Engine.h"

// Sets default values
AVRLocomotionCharacter::AVRLocomotionCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	setupComponents();

	// Setup Variables
	bUseControllerRotationYaw = false;
}

void AVRLocomotionCharacter::setupComponents() {
	HMDOrigin = CreateDefaultSubobject<USceneComponent>(TEXT("HMD Origin"));
	HMDOrigin->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UVRCameraComponent>(TEXT("VR Camera"));
	CameraComponent->SetupAttachment(HMDOrigin);
	CameraComponent->bUseLateUpdate = false;
	CameraComponent->bLockToHmd = 1;

	MCOrigin = CreateDefaultSubobject<USceneComponent>(TEXT("MC Origin"));
	MCOrigin->SetupAttachment(RootComponent);

	LeftMotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Left MC"));
	LeftMotionController->SetupAttachment(MCOrigin);
	LeftMotionController->bDisplayDeviceModel = true;
	LeftMotionController->MotionSource = FName("Left");

	RightMotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Right MC"));
	RightMotionController->SetupAttachment(MCOrigin);
	RightMotionController->bDisplayDeviceModel = true;
	RightMotionController->MotionSource = FName("Right");
}

// Called when the game starts or when spawned
void AVRLocomotionCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Force Reset player rotation incase they spawned facing the wrong way
	SetActorRotation(FRotator(0, 0, 0));

	// Position Motion Controllers
	FQuat deviceRotation;
	GEngine->XRSystem->GetCurrentPose(IXRTrackingSystem::HMDDeviceId, deviceRotation, LastHMDPos);
	MCOrigin->SetRelativeLocation(FVector(LastHMDPos.X, LastHMDPos.Y, LastHMDPos.Z) * -1);
	GEngine->XRSystem->SetTrackingOrigin(EHMDTrackingOrigin::Floor);
}

void AVRLocomotionCharacter::doHMDPosition_Implementation()
{
	// Get New Location
	FVector devicePosition;
	FQuat deviceRotation;
	FVector NewLocation;
	GEngine->XRSystem->GetCurrentPose(IXRTrackingSystem::HMDDeviceId, deviceRotation, devicePosition);

	// Adjust the Player to the new location
	FVector HMDDelta = devicePosition - LastHMDPos;
	NewLocation = HMDDelta + GetActorLocation();
	SetActorLocation(FVector(NewLocation.X, NewLocation.Y, GetActorLocation().Z));

	// Store new Location
	LastHMDPos = devicePosition;

	// Adjust the location of the Motion Controllers
	NewLocation = MCOrigin->GetRelativeLocation() - HMDDelta;
	MCOrigin->SetRelativeLocation(FVector(NewLocation.X, NewLocation.Y, (NewLocation.Z / -2) - (1.5 * GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight())));

	// Reset the location of the Camera;
	HMDOrigin->SetRelativeLocation(FVector(0.f, 0.f, devicePosition.Z - GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()));

	// Adjust the capsule halfheight to be the height of the player;
	GetCapsuleComponent()->SetCapsuleHalfHeight((devicePosition.Z / 2.f) + 15.f);
}

// Called every frame
void AVRLocomotionCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	doHMDPosition();
}

// Called to bind functionality to input
void AVRLocomotionCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

