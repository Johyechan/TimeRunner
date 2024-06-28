// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UI/TRStartWidget.h"
#include "TRStartMode.generated.h"

/**
 * 
 */
UCLASS()
class TIMERUNNER_API ATRStartMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATRStartMode();
	
protected:
	virtual void BeginPlay() override;

private:
	TSubclassOf<class UUserWidget> StartLevelWidgetClass;
	class UTRStartWidget* StartLevelWidget;

};
