// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../Collectible/Coin.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CustomRoot = CreateDefaultSubobject<USceneComponent>(TEXT("CustomRoot"));
	RootComponent = CustomRoot;

	DoorJoin = CreateDefaultSubobject<USceneComponent>(TEXT("DoorJoin"));
	DoorJoin->SetupAttachment(RootComponent);

	BodyComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyComponent"));
	BodyComponent->SetupAttachment(DoorJoin);
	BodyComponent->SetRelativeLocation(FVector(0.f,50.f,50.f));

}


// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	if (CoinClass)
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), CoinClass, TabCoinRef);
		for (int i = 0; i < TabCoinRef.Num(); ++i)
		{
			ACoin* var = Cast<ACoin>(TabCoinRef[i]);
			var->ParentRef = this;
		}
	}
}

void ADoor::SetDoorRotation(float CurrentRotation)
{
	DoorJoin->SetRelativeRotation(FRotator(0.f, FMath::Lerp(0.f, DoorAngle, CurrentRotation), 0.f));
	return;
}

void ADoor::RemoveCoin(ACoin* target)
{
	TabCoinRef.Remove(target);
	if (TabCoinRef.IsEmpty())
	{
		OpenDoor();
	}
}

void ADoor::OpenDoor_Implementation()
{}
