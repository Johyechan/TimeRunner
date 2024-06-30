// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "TRGoalFloor.generated.h"

UCLASS()
class TIMERUNNER_API ATRGoalFloor : public AActor
{
	GENERATED_BODY()
	
public:
	ATRGoalFloor();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* GoalFloorMesh;
};
