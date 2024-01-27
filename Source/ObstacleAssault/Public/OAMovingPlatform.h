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

	void Move();

	UPROPERTY(EditAnywhere)
	FVector StartPosition = FVector(8,8,23);

	UPROPERTY(EditAnywhere)
	FVector EndPosition = FVector(8,8,23);

	UPROPERTY(EditDefaultsOnly)
	float Delay = 2;
	
	UPROPERTY(EditDefaultsOnly)
	float Speed = 1;

	UPROPERTY(EditDefaultsOnly)
	float MoveRate = .01;

	UPROPERTY(EditDefaultsOnly)
	float Deviation = 1;

	UPROPERTY(VisibleAnywhere)
	FVector TargetPosition = FVector();

	UPROPERTY()
	FVector Direction = FVector();

	FTimerHandle MoveTimer;
};
