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
	SetActorLocation(CurrentActorLocation + Offset);
	if (FVector::Distance(Origin, GetActorLocation()) < Direction.Length())
	{
		return;
	}
	SetActorTickEnabled(false);
	GetWorld()->GetTimerManager().SetTimer(MoveTimer, this, &AOAMovingPlatform::SwitchDirection, Delay);
}

// Called every frame
void AOAMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);
}



