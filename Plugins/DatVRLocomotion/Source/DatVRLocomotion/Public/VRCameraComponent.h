// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "VRCameraComponent.generated.h"

/**
 * A Modification to the default camera that forces the camera to only lock onto the HMD orientation, not the location
 */
UCLASS(HideCategories = (Mobility, Rendering, LOD), Blueprintable, ClassGroup = Camera, meta = (BlueprintSpawnableComponent))
class DATVRLOCOMOTION_API UVRCameraComponent : public UCameraComponent
{
	GENERATED_BODY()
public:
	/*
	 * This will use a late update on the render thread. Use this for VR if you aren't locking the HMD.
	 * This feature in my experience its extremely nausiating, you have been warned
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CameraOptions)
	bool bUseLateUpdate = false;

	/**
	 * Returns camera's Point of View.
	 * Called by Camera class. Subclass and postprocess to add any effects.
	 */
	virtual void GetCameraView(float DeltaTime, FMinimalViewInfo& DesiredView) override;
};
