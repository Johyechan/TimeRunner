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
	// Actor�� �ð� �帧�� CustomTimeDilation * GlobalTimeDilation�� ���� �ȴ� �׷��� �������� �� �ð����� 1�� ������ ��������� �ð��� �������� �� �⺻ �ð��� 1�� �ǵ��� CustomTimeDilation�� 1 / NewTime(������ �ð��� ��ġ)�� �Ѵ�.
	CustomTimeDilation = 1.0f / NewTime;

	// NewTime��ŭ �������� �Ѵ�
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), NewTime);

	// Ÿ�̸� ���� ���� �ð� ���� ���� ����
	float CurrentTimeDilation = GetWorld()->GetWorldSettings()->TimeDilation;

	// ��ٸ��� �ð� (���� ����)
	float WaitTimeSlow = Duration;

	// ���� ��ٸ��� �ð� ��� (���� ����) �����Ⱑ �ƴ� ���ϱ⸦ �� ������ �����⸦ �ϰԵǸ� ������ ���� ������ �ǰ� �������鼭 ���� �� Ŀ���� ������ �÷��̾��� �ð� ��ü�� �� ����� �ٸ� ���� �Ⱥ��̱� ������ �����⸦ ����� �̰��� ������ ��ŭ �� ���� �� �ð��� ���� �۾ƾ� ������ ���ϱ⸦ �����.
	float RealWaitTime = WaitTimeSlow * CurrentTimeDilation;

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATRCharacterPlayer::ResetTime, RealWaitTime, false);
}

void ATRCharacterPlayer::ResetTime()
{
	CustomTimeDilation = 1.0f;

	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
}
