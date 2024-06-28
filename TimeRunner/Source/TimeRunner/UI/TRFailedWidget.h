// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "TRFailedWidget.generated.h"

/**
 * 
 */
UCLASS()
class TIMERUNNER_API UTRFailedWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	UButton* ReturnButton;

	UFUNCTION()
	void OnReturnButtonClicked();
};
