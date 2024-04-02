// Fill out your copyright notice in the Description page of Project Settings.

#include "ObstacleAssault/Public/OAMovingPlatform.h"

// Sets default values
AOAMovingPlatform::AOAMovingPlatform()
{
	SetActorTickEnabled(false);
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AOAMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	InitializeMove();	
}

void AOAMovingPlatform::InitializeMove()
{
	StartPosition = GetActorLocation();
	EndPosition = StartPosition + Direction;
	Origin = StartPosition;
	SetActorTickEnabled(true);
}

void AOAMovingPlatform::SwitchDirection()
{
	Origin = (Origin == EndPosition) ? StartPosition : EndPosition;
	Direction *= -1;
	SetActorTickEnabled(true);
}

double AOAMovingPlatform::GetDistanceMoved(const FVector& CurrentLocation) const
{
	return FVector::Distance(Origin, CurrentLocation);
}

void AOAMovingPlatform::Move(float DeltaTime)
{
	if (Direction.Length() == 0)
	{
		return;
	}
	const FVector Offset = Direction.GetSafeNormal() * (Speed * DeltaTime);
	if (GetDistanceMoved((GetActorLocation() + Offset)) < Direction.Length())
	{
		SetActorLocation(GetActorLocation() + Offset);
		return;
	}
	SetActorLocation(Origin + Direction);
	SetActorTickEnabled(false);
	GetWorld()->GetTimerManager().SetTimer(MoveTimer, this, &AOAMovingPlatform::SwitchDirection, Delay);
}

void AOAMovingPlatform::Rotate(float DeltaTime)
{
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}

// Called every frame
void AOAMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);
	Rotate(DeltaTime);
}



