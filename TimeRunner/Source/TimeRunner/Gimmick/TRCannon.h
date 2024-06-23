// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TRCannon.generated.h"

UCLASS()
class TIMERUNNER_API ATRCannon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATRCannon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	float FireInterval;

	FVector FirePos;

	FRotator CannonBallRotation;

	FTimerHandle TimerHandle;

	void StartFire();

	void StopFire();

	void CreateCannonBall();
};
