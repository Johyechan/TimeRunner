// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TRFailedWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

void UTRFailedWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ReturnButton)
	{
		ReturnButton->OnClicked.AddDynamic(this, &UTRFailedWidget::OnReturnButtonClicked);
	}
}

void UTRFailedWidget::OnReturnButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("StartLevel"));
}
