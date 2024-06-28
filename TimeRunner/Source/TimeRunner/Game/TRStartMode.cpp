// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/TRStartMode.h"
#include "UI/TRStartWidget.h"

ATRStartMode::ATRStartMode()
{
	static ConstructorHelpers::FClassFinder<UTRStartWidget> StartWidgetClass(TEXT("/Game/TimeRunner/UI/WBP_StartUI.WBP_StartUI_C"));
	if (StartWidgetClass.Succeeded())
	{
		StartLevelWidgetClass = StartWidgetClass.Class;
	}
}

void ATRStartMode::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->SetShowMouseCursor(true);
	}

	if (IsValid(StartLevelWidgetClass))
	{
		// ������ �����Ѵ�
		StartLevelWidget = Cast<UTRStartWidget>(CreateWidget(GetWorld(), StartLevelWidgetClass));

		if (IsValid(StartLevelWidget))
		{
			// ������ ����Ʈ�� �߰��Ѵ�
			StartLevelWidget->AddToViewport();
		}
	}
}
