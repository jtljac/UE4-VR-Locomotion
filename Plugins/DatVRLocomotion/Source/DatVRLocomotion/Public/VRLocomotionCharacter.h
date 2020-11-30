// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VRCameraComponent.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h"
#include "VRLocomotionCharacter.generated.h"

UCLASS(BlueprintType)
class DATVRLOCOMOTION_API AVRLocomotionCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVRLocomotionCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
	void doHMDPosition();
	virtual void setupComponents();

	// Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HMD")
	FVector LastHMDPos;

public:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USceneComponent* HMDOrigin;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UVRCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USceneComponent* MCOrigin;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UMotionControllerComponent* LeftMotionController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UMotionControllerComponent* RightMotionController;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
};
