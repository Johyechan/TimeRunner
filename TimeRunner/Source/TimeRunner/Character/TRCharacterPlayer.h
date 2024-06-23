// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TRCharacterBase.h"
#include "InputActionValue.h"
#include "TRCharacterPlayer.generated.h"

/**
 * 
 */
UCLASS()
class TIMERUNNER_API ATRCharacterPlayer : public ATRCharacterBase
{
	GENERATED_BODY()
	
public:
	ATRCharacterPlayer();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// Camera Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;

// Input Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> TimeSlowAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

// Time Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Timer, Meta = (AllowPrivateAccess = "true"))
	float NewTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Timer, Meta = (AllowPrivateAccess = "true"))
	float Duration;

	void TimeSlow(const FInputActionValue& Value);
	void ResetTime();
};
