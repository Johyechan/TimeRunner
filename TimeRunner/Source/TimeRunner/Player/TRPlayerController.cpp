// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TRPlayerController.h"

void ATRPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}
