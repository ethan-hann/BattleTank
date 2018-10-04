// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"

//TODO: REMOVE HARD CODED MESH
UTankTurret::UTankTurret()
{
	/*static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("/Game/Meshes/Tank/tank_fbx_Turret.tank_fbx_Turret"));
	this->SetStaticMesh(MeshAsset.Object);*/
}

void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0.f, Rotation, 0.f));
}


