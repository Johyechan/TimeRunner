// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TRCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATRCharacterBase::ATRCharacterBase()
{
    // Pawn
    bUseControllerRotationPitch = false; bUseControllerRotationYaw = false; bUseControllerRotationRoll = false;

    // Capsule
    GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f); GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

    //Movement
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 600.0f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.0f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;

    // Mesh
    GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f)); 
    GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint); GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh"));

    static ConstructorHelpers::FObjectFinder<USkeletalMesh>CharacterMeshRef(TEXT("/Game/Characters/Mannequins/Meshes/SKM_Quinn_Simple.SKM_Quinn_Simple"));

    if (CharacterMeshRef.Object)
    { 
        GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object); 
    }

    static ConstructorHelpers::FClassFinder<UAnimInstance>AnimInstanceClassRef(TEXT("/Game/TimeRunner/Animation/ABP_TRCharacter.ABP_TRCharacter_C"));

    if (AnimInstanceClassRef.Class)
    {
        GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
    }

    GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ATRCharacterBase::OnHit);
}

void ATRCharacterBase::Tick(float DeltaTime)
{
    // 만약 일정 z축 이하로 떨어지면 사망
    FVector CurrentLocation = GetActorLocation();
    if (CurrentLocation.Z < -460)
    {
        UGameplayStatics::OpenLevel(GetWorld(), FName("FailedLevel"));
    }
}

void ATRCharacterBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor && OtherActor != this && OtherComp)
    {
        FString OtherActorName = OtherActor->GetName();

        if (OtherActorName.Contains("CannonBall"))
        {
            UGameplayStatics::OpenLevel(GetWorld(), FName("FailedLevel"));
        }

        if (OtherActorName.Contains("GoalFloor"))
        {
            UGameplayStatics::OpenLevel(GetWorld(), FName("GoalLevel"));
        }
    }
}

