// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/TRCannon.h"
#include "Gimmick/TRCannonBall.h"
#include "GameFramework/Actor.h"

// Sets default values
ATRCannon::ATRCannon()
{
	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonMesh"));
	RootComponent = CannonMesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CannonCylinderMeshRef(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	if (CannonCylinderMeshRef.Object)
	{
		CannonMesh->SetStaticMesh(CannonCylinderMeshRef.Object);
	}
	CannonMesh->SetRelativeRotation(FRotator(90.0f, 90.0f, 0.0f));

	FireLocation = CreateDefaultSubobject<USceneComponent>(TEXT("FireLocation"));
	FireLocation->SetupAttachment(CannonMesh);
	FireLocation->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	FireLocation->SetRelativeRotation(FRotator(270.0, 90.0f, 0.0f));
}

// Called when the game starts or when spawned
void ATRCannon::BeginPlay()
{
	Super::BeginPlay();
	
	StartFire();
}

void ATRCannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATRCannon::StartFire()
{
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATRCannon::CreateCannonBall, FireInterval, true);
}

void ATRCannon::StopFire()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);
}

void ATRCannon::CreateCannonBall()
{
	FirePos = FireLocation->GetComponentLocation();
	CannonBallRotation = FireLocation->GetComponentRotation();

	FActorSpawnParameters CannonBallSpawnParams;
	CannonBallSpawnParams.Owner = this;
	CannonBallSpawnParams.Instigator = GetInstigator();

	ATRCannonBall* NewCannonBall = GetWorld()->SpawnActor<ATRCannonBall>(CannonBallClass, FirePos, CannonBallRotation, CannonBallSpawnParams);
}

