// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UI/TRGoalWidget.h"
#include "TRGoalMode.generated.h"

/**
 * 
 */
UCLASS()
class TIMERUNNER_API ATRGoalMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ATRGoalMode();

protected:
	virtual void BeginPlay() override;

private:
	TSubclassOf<class UUserWidget> GoalLevelWidgetClass;
	class UTRGoalWidget* GoalLevelWidget;
};
