// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "TRStartWidget.generated.h"

/**
 * 
 */
UCLASS()
class TIMERUNNER_API UTRStartWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UTRStartWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	UButton* StartButton;

	UFUNCTION()
	void OnQuitButtonClicked();

	UFUNCTION()
	void OnStartButtonClicked();
};
