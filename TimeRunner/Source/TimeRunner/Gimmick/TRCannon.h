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

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* CannonMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TSubclassOf<class ATRCannonBall> CannonBallClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* FireLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon")
	float FireInterval;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pos")
	FVector FirePos;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rotation")
	FRotator CannonBallRotation;

	FTimerHandle TimerHandle;

	void StartFire();

	void StopFire();

	void CreateCannonBall();
};
