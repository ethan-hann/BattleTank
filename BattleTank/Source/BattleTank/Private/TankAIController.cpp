// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "GameFramework/PlayerController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Tank.h"
#include "GameFramework/Pawn.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!PlayerTank && !ControlledTank) { return; }
	//Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius); //TODO: check radius is in centimeters

	//Aim towards the player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (PlayerTank)
	{ 
		AimingComponent->AimAt(PlayerTank->GetActorLocation()); 
	}
	
	//If aiming or locked, then fire
	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire(); //TODO: don't fire every frame; limit firing rate
	}
}

//Set OnDeath delegate here so we don't have to worry about race conditions
void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (!InPawn) { return; }

	auto PossessedTank = Cast<ATank>(InPawn);

	if (!ensure(PossessedTank)) { return; }

	//Subscribe our local method to the Tank's death event
	PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);
}

void ATankAIController::OnPossedTankDeath()
{
	if (!GetPawn()) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}

