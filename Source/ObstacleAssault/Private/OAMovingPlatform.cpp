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
	if (Direction.Length() == 0)
	{
		SetActorLocation(StartPosition);
		Direction = EndPosition - StartPosition;
	}
	else
	{
		StartPosition = GetActorLocation();
		EndPosition = StartPosition + Direction;
	}
	Origin = StartPosition;
	SetActorTickEnabled(true);
}

void AOAMovingPlatform::SwitchDirection()
{
	Origin = (Origin == EndPosition) ? StartPosition : EndPosition;
	Direction *= -1;
	SetActorTickEnabled(true);
}

void AOAMovingPlatform::Move(float DeltaTime)
{
	const FVector CurrentActorLocation = GetActorLocation();
	const FVector Offset = Direction.GetSafeNormal() * (Speed * DeltaTime);
	const double DistanceMoved = FVector::Distance(Origin, (GetActorLocation() + Offset));
	if (DistanceMoved < Direction.Length())
	{
		SetActorLocation(CurrentActorLocation + Offset);
		return;
	}
	SetActorLocation(Origin + Direction);
	const double OverShoot = DistanceMoved - Direction.Length();
	//UE_LOG(LogTemp, Log, TEXT("Platform with name: %s\n overshoot eith value: %f"), *GetName(), OverShoot);
	SetActorTickEnabled(false);
	GetWorld()->GetTimerManager().SetTimer(MoveTimer, this, &AOAMovingPlatform::SwitchDirection, Delay);
}

// Called every frame
void AOAMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);
}



