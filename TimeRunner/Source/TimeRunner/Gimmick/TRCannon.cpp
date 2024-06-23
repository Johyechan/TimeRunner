// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/TRCannon.h"
#include "Gimmick/TRCannonBall.h"

// �̰� ���� ���� ���� ����?
// Sets default values
ATRCannon::ATRCannon()
{
	FireInterval = 2.0f;
}

// Called when the game starts or when spawned
void ATRCannon::BeginPlay()
{
	Super::BeginPlay();
	
	StartFire();
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
	FActorSpawnParameters CannonBallSpawnParams;
	CannonBallSpawnParams.Owner = this;

	ATRCannonBall* NewCannonBall = GetWorld()->SpawnActor<ATRCannonBall>(FirePos, CannonBallRotation, CannonBallSpawnParams);
}

