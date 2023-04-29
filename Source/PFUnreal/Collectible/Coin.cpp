// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "GameFramework/Character.h"
#include "../Public/Door.h"

// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxCollide = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = BoxCollide;


	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	Body->SetupAttachment(BoxCollide);
	Body->SetStaticMesh(BodyMesh);
	

	RotationComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotationComponent"));
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();
	
	BoxCollide->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnOverlap);
}

void ACoin::OnOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	if (Cast<ACharacter>(OtherActor))
	{
		if (ParentRef)
		{
			ParentRef->RemoveCoin(this);
		}
		UE_LOG(LogTemp, Warning, TEXT("Collision!!!!"));
		Destroy();
	}
}

