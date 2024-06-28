// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TRGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TIMERUNNER_API ATRGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ATRGameMode();

protected:
	virtual void BeginPlay() override;
};
