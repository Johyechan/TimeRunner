// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TRCharacterPlayer.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ATRCharacterPlayer::ATRCharacterPlayer()
{
	// Camera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 100.0f);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	FollowCamera->SetWorldLocation(FVector(0.0f, 0.0f, 150.0f));
	FollowCamera->SetWorldRotation(FRotator(-35.0f, 0.0f, 0.0f));

	// Input
	static ConstructorHelpers::FObjectFinder<UInputMappingContext>InputMappingContextRef(TEXT("/Game/TimeRunner/Input/IMC_Default.IMC_Default"));
	if (nullptr != InputMappingContextRef.Object)
	{
		DefaultMappingContext = InputMappingContextRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>InputActionJumpRef(TEXT("/Game/TimeRunner/Input/Actions/IA_Jump.IA_Jump"));
	if (nullptr != InputActionJumpRef.Object)
	{
		JumpAction = InputActionJumpRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>InputActionMoveRef(TEXT("/Game/TimeRunner/Input/Actions/IA_Move.IA_Move"));
	if (nullptr != InputActionMoveRef.Object)
	{
		MoveAction = InputActionMoveRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>InputActionLookRef(TEXT("/Game/TimeRunner/Input/Actions/IA_Look.IA_Look"));
	if (nullptr != InputActionLookRef.Object)
	{
		LookAction = InputActionLookRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>InputActionTimeSlowRef(TEXT("/Game/TimeRunner/Input/Actions/IA_TimeSlow.IA_TimeSlow"));
	if (nullptr != InputActionTimeSlowRef.Object)
	{
		TimeSlowAction = InputActionTimeSlowRef.Object;
	}

	// Time
	NewTime = 0.5f;
	Duration = 1.0f;
}

void ATRCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ATRCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this,&ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this,&ACharacter::StopJumping);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this,&ATRCharacterPlayer::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this,&ATRCharacterPlayer::Look);
	EnhancedInputComponent->BindAction(TimeSlowAction, ETriggerEvent::Triggered, this, &ATRCharacterPlayer::TimeSlow);
}

void ATRCharacterPlayer::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector FowardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(FowardDirection, MovementVector.X);
	AddMovementInput(RightDirection, MovementVector.Y);
}

void ATRCharacterPlayer::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerYawInput(LookAxisVector.Y);
}

void ATRCharacterPlayer::TimeSlow(const FInputActionValue& Value)
{
	// Actor의 시간 흐름은 CustomTimeDilation * GlobalTimeDilation의 값이 된다 그래서 느려지게 될 시간으로 1을 나누어 결과적으로 시간이 느려졌을 때 기본 시간인 1이 되도록 CustomTimeDilation을 1 / NewTime(느려진 시간의 수치)로 한다.
	CustomTimeDilation = 1.0f / NewTime;

	// NewTime만큼 느려지게 한다
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), NewTime);

	// 타이머 설정 전에 시간 감속 비율 저장
	float CurrentTimeDilation = GetWorld()->GetWorldSettings()->TimeDilation;

	// 기다리는 시간 (감속 적용)
	float WaitTimeSlow = Duration;

	// 실제 기다리는 시간 계산 (감속 보정) 나누기가 아닌 곱하기를 한 이유는 나누기를 하게되면 나누는 값이 역수가 되고 곱해지면서 값이 더 커지기 때문에 플레이어의 시간 자체는 더 빨라야 다른 점이 안보이기 때문에 나누기를 해줬고 이것은 느려진 만큼 더 빨리 즉 시간의 값이 작아야 함으로 곱하기를 해줬다.
	float RealWaitTime = WaitTimeSlow * CurrentTimeDilation;

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATRCharacterPlayer::ResetTime, RealWaitTime, false);
}

void ATRCharacterPlayer::ResetTime()
{
	CustomTimeDilation = 1.0f;

	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
}
