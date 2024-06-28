// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/TRGoalMode.h"
#include "UI/TRGoalWidget.h"

ATRGoalMode::ATRGoalMode()
{
	static ConstructorHelpers::FClassFinder<UTRGoalWidget> GoalWidgetClass(TEXT("/Game/TimeRunner/UI/WBP_GoalUI.WBP_GoalUI_C"));
	if (GoalWidgetClass.Succeeded())
	{
		GoalLevelWidgetClass = GoalWidgetClass.Class;
	}
}

void ATRGoalMode::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->SetShowMouseCursor(true);
	}

	if (IsValid(GoalLevelWidgetClass))
	{
		// ������ �����Ѵ�
		GoalLevelWidget = Cast<UTRGoalWidget>(CreateWidget(GetWorld(), GoalLevelWidgetClass));

		if (IsValid(GoalLevelWidget))
		{
			// ������ ����Ʈ�� �߰��Ѵ�
			GoalLevelWidget->AddToViewport();
		}
	}
}
