// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UI/TRFailedWidget.h"
#include "TRFailedMode.generated.h"

/**
 * 
 */
UCLASS()
class TIMERUNNER_API ATRFailedMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ATRFailedMode();

protected:
	virtual void BeginPlay() override;

private:
	TSubclassOf<class UUserWidget> FailedLevelWidgetClass;
	class UTRFailedWidget* FailedLevelWidget;
};
