// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/TRGameMode.h"
#include "TRGameMode.h"
#include "Player/TRPlayerController.h"

ATRGameMode::ATRGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn>DefaultPawnClassRef(TEXT("/Script/TimeRunner.TRCharacterPlayer"));
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}


	static ConstructorHelpers::FClassFinder<APlayerController>PlayerControllerClassRef(TEXT("/Script/TimeRunner.TRPlayerController"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}
}

void ATRGameMode::BeginPlay()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->SetShowMouseCursor(false);
	}
}


