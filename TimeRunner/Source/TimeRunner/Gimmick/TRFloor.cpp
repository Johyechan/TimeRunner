// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/TRFloor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ATRFloor::ATRFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TRFloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
	RootComponent = TRFloorMesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>FloorMeshRef(TEXT("/Engine/BasicShapes/Cube"));
	if (FloorMeshRef.Object)
	{
		TRFloorMesh->SetStaticMesh(FloorMeshRef.Object);
	}

	TRFloorMesh->SetWorldScale3D(FVector(1.5f, 3.0f, 0.2f));
}

// Called when the game starts or when spawned
void ATRFloor::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();
	TargetLocation = StartLocation;
}

// Called every frame
void ATRFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetCurrentLocation(IsX, IsY, IsZ);
}

void ATRFloor::SetCurrentLocation(bool X, bool Y, bool Z)
{
	FVector CurrentLocation = GetActorLocation();

	if (IsZ)
	{
		if (Amplitude != 0.0f && Frequency != 0.0f)
		{
			CurrentLocation.Z = StartLocation.Z + DeltaMove();
		}
	}
	else if (IsX)
	{
		if (Amplitude != 0.0f && Frequency != 0.0f)
		{
			CurrentLocation.X = StartLocation.X + DeltaMove();
		}
	}
	else if (IsY)
	{
		if (Amplitude != 0.0f && Frequency != 0.0f)
		{
			CurrentLocation.Y = StartLocation.Y + DeltaMove();
		}
	}

	SetActorLocation(CurrentLocation);
}

float ATRFloor::DeltaMove()
{
	float DeltaMoveValue = FMath::Sin(GetWorld()->TimeSeconds * Frequency) * Amplitude;
	return DeltaMoveValue;
}

