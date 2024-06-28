// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/TRFailedMode.h"
#include "UI/TRFailedWidget.h"

ATRFailedMode::ATRFailedMode()
{
	static ConstructorHelpers::FClassFinder<UTRFailedWidget> FailedWidgetClass(TEXT("/Game/TimeRunner/UI/WBP_FailedUI.WBP_FailedUI_C"));
	if (FailedWidgetClass.Succeeded())
	{
		FailedLevelWidgetClass = FailedWidgetClass.Class;
	}
}

void ATRFailedMode::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->SetShowMouseCursor(true);
	}

	if (IsValid(FailedLevelWidgetClass))
	{
		// ������ �����Ѵ�
		FailedLevelWidget = Cast<UTRFailedWidget>(CreateWidget(GetWorld(), FailedLevelWidgetClass));

		if (IsValid(FailedLevelWidget))
		{
			// ������ ����Ʈ�� �߰��Ѵ�
			FailedLevelWidget->AddToViewport();
		}
	}
}
