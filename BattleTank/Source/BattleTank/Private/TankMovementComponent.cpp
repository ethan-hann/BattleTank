//Copyright Kelvin's Games 2018

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialze(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!ensure(LeftTrackToSet && RightTrackToSet)) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//No need to call Super, as we're replacing the functionality
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);

	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendTurnRight(RightThrow);
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	Throw = FMath::Clamp<float>(Throw, -1.f, 1.f);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	Throw = FMath::Clamp<float>(Throw, -1.f, 1.f);  //clamped to prevent turning to fast
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::Reset()
{
	FVector CurrentPosition = GetOwner()->GetActorLocation();
	FVector NewLocation = FVector(CurrentPosition.X, CurrentPosition.Y, 100.f);
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	FRotator NewRotation = FRotator(CurrentRotation.Pitch, CurrentRotation.Yaw, 0.0f);
	GetOwner()->SetActorLocationAndRotation(NewLocation, NewRotation, false);
}



