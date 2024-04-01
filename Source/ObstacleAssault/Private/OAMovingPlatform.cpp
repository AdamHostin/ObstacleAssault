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

double AOAMovingPlatform::GetDistanceMoved(const FVector& CurrentLocation)
{
	return FVector::Distance(Origin, CurrentLocation);
}

void AOAMovingPlatform::Move(float DeltaTime)
{
	const FVector Offset = Direction.GetSafeNormal() * (Speed * DeltaTime);
	if (GetDistanceMoved((GetActorLocation() + Offset)) < Direction.Length())
	{
		SetActorLocation(GetActorLocation() + Offset);
		return;
	}
	SetActorLocation(Origin + Direction);
	const double OverShoot = GetDistanceMoved(GetActorLocation()) - Direction.Length();
	UE_LOG(LogTemp, Log, TEXT("Platform with name: %s\n overshoot eith value: %f"), *GetName(), OverShoot);
	SetActorTickEnabled(false);
	GetWorld()->GetTimerManager().SetTimer(MoveTimer, this, &AOAMovingPlatform::SwitchDirection, Delay);
}

void AOAMovingPlatform::Rotate(float DeltaTime)
{
	UE_LOG(LogTemp, Log, TEXT("Platform with name: %s\n wanabe rotating"), *GetName());
}

// Called every frame
void AOAMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);
	Rotate(DeltaTime);
}



