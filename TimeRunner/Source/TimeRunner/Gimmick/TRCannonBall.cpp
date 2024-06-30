// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/TRCannonBall.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ATRCannonBall::ATRCannonBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(15.0f);
	CollisionComponent->SetCollisionProfileName(TEXT("CannonBall"));
	RootComponent = CollisionComponent;

	CannonBallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonBallMesh"));
	CannonBallMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>CannonBallMeshRef(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (CannonBallMeshRef.Object)
	{
		CannonBallMesh->SetStaticMesh(CannonBallMeshRef.Object);
	}

	CannonBallMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("CannonBallMovement"));
	CannonBallMovement->UpdatedComponent = CollisionComponent;
	CannonBallMovement->InitialSpeed = 3000.0f;
	CannonBallMovement->MaxSpeed = 2000.0f;
	CannonBallMovement->ProjectileGravityScale = 0;
	CannonBallMovement->bRotationFollowsVelocity = true;
	CannonBallMovement->bShouldBounce = true;

	LifeTime = 2.0f;
}

// Called when the game starts or when spawned
void ATRCannonBall::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(LifeTime);
}

// Called every frame
void ATRCannonBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

