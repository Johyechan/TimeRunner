// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TRGoalWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

void UTRGoalWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ReturnButton)
	{
		ReturnButton->OnClicked.AddDynamic(this, &UTRGoalWidget::OnReturnButtonClicked);
	}
}

void UTRGoalWidget::OnReturnButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("StartLevel"));
}
