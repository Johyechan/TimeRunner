// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TRStartWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

UTRStartWidget::UTRStartWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UTRStartWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UTRStartWidget::OnQuitButtonClicked);
	}

	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UTRStartWidget::OnStartButtonClicked);
	}
}

void UTRStartWidget::OnQuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}

void UTRStartWidget::OnStartButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("Step1"));
}
