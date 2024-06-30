// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/TRGoalFloor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ATRGoalFloor::ATRGoalFloor()
{
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	CollisionComponent->InitBoxExtent(FVector(10, 10, 2));
	CollisionComponent->SetCollisionProfileName(TEXT("GoalFloor"));
	RootComponent = CollisionComponent;

	GoalFloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GoalFloorMesh"));
	GoalFloorMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>GoalFloorMeshRef(TEXT("/Engine/BasicShapes/Cube"));
	if (GoalFloorMeshRef.Object)
	{
		GoalFloorMesh->SetStaticMesh(GoalFloorMeshRef.Object);
	}
}

