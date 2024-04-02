// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OAMovingPlatform.generated.h"

UCLASS()
class OBSTACLEASSAULT_API AOAMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOAMovingPlatform();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void InitializeMove();

	void SwitchDirection();

	double GetDistanceMoved(const FVector& CurrentLocation) const;

	void Move(float DeltaTime);

	void Rotate(float DeltaTime);

	UPROPERTY(EditAnywhere)
	FVector StartPosition = FVector(8,8,23);

	UPROPERTY(VisibleAnywhere)
	FVector EndPosition = FVector(8,8,23);

	UPROPERTY(EditAnywhere)
	FVector Direction;

	UPROPERTY(VisibleAnywhere)
	FVector Origin;

	UPROPERTY(EditAnywhere)
	FRotator RotationVelocity;

	UPROPERTY(EditDefaultsOnly)
	float Delay = 2;
	
	UPROPERTY(EditDefaultsOnly)
	float Speed = 1;
	
	FTimerHandle MoveTimer;
};
