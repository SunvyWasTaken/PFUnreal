// Fill out your copyright notice in the Description page of Project Settings.


#include "Spike.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../PFUnrealCharacter.h"

// Sets default values
ASpike::ASpike()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;


	BodyComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyComponent"));
	BodyComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASpike::BeginPlay()
{
	Super::BeginPlay();
	
	//BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ASpike::OnOverlap);
	BoxCollision->OnComponentHit.AddDynamic(this, &ASpike::OnHit);
}

void ASpike::OnOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	if(APFUnrealCharacter* PlayerRef = Cast<APFUnrealCharacter>(OtherActor))
	{
		BoxCollision->SetCollisionEnabled(ECollisionEnabled::ProbeOnly); // <- essais pour que le overlap ne se fasse qu'une fois.
		PlayerRef->ApplyDamage();
		BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // <- essais pour que le overlap ne se fasse qu'une fois.
	}
}

void ASpike::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(APFUnrealCharacter* PlayerRef = Cast<APFUnrealCharacter>(OtherActor))
		PlayerRef->ApplyDamage();
}

