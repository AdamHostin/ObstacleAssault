// Fill out your copyright notice in the Description page of Project Settings.

#include "ObstacleAssault/Public/OAMovingPlatform.h"

// Sets default values
AOAMovingPlatform::AOAMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOAMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	SetActorLocation(StartPosition);
	InitializeMove();	
}

void AOAMovingPlatform::InitializeMove()
{
	TargetPosition = (TargetPosition == EndPosition) ? StartPosition : EndPosition;
	Direction = (TargetPosition - GetActorLocation());
	Direction.Normalize();
	GetWorld()->GetTimerManager().SetTimer(MoveTimer, this, &AOAMovingPlatform::Move, MoveRate, true);
}

void AOAMovingPlatform::Move()
{
	FVector CurrentActorLocation = GetActorLocation();
	SetActorLocation(CurrentActorLocation + (Direction*Speed));
	if (FVector::Distance(TargetPosition, GetActorLocation()) <= Deviation)
	{
		GetWorld()->GetTimerManager().SetTimer(MoveTimer, this, &AOAMovingPlatform::InitializeMove, Delay);
	}
}

// Called every frame
void AOAMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

