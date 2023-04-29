// Fill out your copyright notice in the Description page of Project Settings.


#include "EndZone.h"
#include "Components/BoxComponent.h"
#include "../PFUnrealGameMode.h"
#include "GameFramework/Character.h"

// Sets default values
AEndZone::AEndZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;

}

// Called when the game starts or when spawned
void AEndZone::BeginPlay()
{
	Super::BeginPlay();
	
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AEndZone::OnOverlap);
}

void AEndZone::OnOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	if (Cast<ACharacter>(OtherActor))
	{
		APFUnrealGameMode* GameModeRef = Cast<APFUnrealGameMode>(GetWorld()->GetAuthGameMode());
		GameModeRef->DisplayEndScreen();
	}
}

