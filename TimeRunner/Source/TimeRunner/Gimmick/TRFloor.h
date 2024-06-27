// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TRFloor.generated.h"

UCLASS()
class TIMERUNNER_API ATRFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATRFloor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	FVector StartLocation;
	FVector TargetLocation;

	UPROPERTY(EditAnywhere, Category = "Platform Movement")
	float Amplitude = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Platform Movement")
	float Frequency = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floor")
	bool IsX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floor")
	bool IsY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floor")
	bool IsZ;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TRFloorMesh;

	void SetCurrentLocation(bool X, bool Y, bool Z);

	float DeltaMove();
};
