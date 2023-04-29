// Fill out your copyright notice in the Description page of Project Settings.


#include "DashComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../PFUnrealCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UDashComponent::UDashComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	Activate(true);

	// ...
}

void UDashComponent::BeginPlay()
{
	Super::BeginPlay();

	if (APawn* CheckPawn = Cast<APawn>(GetOwner()))
	{
		PlayerControllerRef = Cast<APlayerController>(CheckPawn->GetController());
	}
}

void UDashComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!IsActive())
	{
		return;
	}
	if(IsDashing)
		LerpPlayer(DeltaTime);
}

FVector UDashComponent::GetDirection(float Cos, float Sin)
{
	FVector Direction;
	Direction = ForwardDirection * (Cos * (DDistance / 2));
	Direction += RightDirection * (Sin * (DDistance / 2) * DashDistorsion);
	return Direction;
}

void UDashComponent::Dash(bool IsLeft)
{
	UE_LOG(LogTemp, Warning, TEXT("Dash!!"));
	if (!IsActive() || IsDashing)
	{
		UE_LOG(LogTemp, Warning, TEXT("Dash fail : %f"), IsLeft);
		return;
	}
	float Angle = DashDegree / DDivision;
	/// Convert en radians parce que Unreal m'envoie chier avec cos(60°) = -0.9
	Angle =	FMath::DegreesToRadians(Angle);

	StartLocation = GetOwner()->GetActorLocation();
	ForwardDirection = GetOwner()->GetActorForwardVector();
	if (IsLeft)
		RightDirection = GetOwner()->GetActorRightVector() * -1;
	else
		RightDirection = GetOwner()->GetActorRightVector();
	
	FVector EndLocation = StartLocation + ForwardDirection * DDistance;

	FHitResult OutHitGround;
	if (!GetWorld()->LineTraceSingleByChannel(OutHitGround, EndLocation, EndLocation + FVector::DownVector*100.f, ECC_Visibility))
	{
		return;
	}

	// Save pour évité de recalculer la même position
	FVector PreLocation;

	for (int i = 0; i <= DDivision-1; ++i)
	{
		float SinValue;
		float CosValue;

		FVector TargetLocation;

		// calcule pour le premier tick
		if (i == 0)
		{
			FMath::SinCos(&SinValue, &CosValue, 0);

			TargetLocation = GetDirection(CosValue, SinValue) + (StartLocation + ForwardDirection * (DDistance / 2));
		}
		else
			TargetLocation = PreLocation;

		const TArray<AActor*> ActorToIgnor;	
		FHitResult OutHit;

		FMath::SinCos(&SinValue, &CosValue, (Angle * (i + 1)));

		PreLocation = GetDirection(CosValue, SinValue) + (StartLocation + ForwardDirection * (DDistance / 2));

		UKismetSystemLibrary::CapsuleTraceSingle(GetWorld(), TargetLocation, PreLocation, 35.f, 90.f, UEngineTypes::ConvertToTraceType(ECC_Visibility), false, ActorToIgnor, EDrawDebugTrace::ForDuration, OutHit, true);


		if (OutHit.bBlockingHit)
		{
			return;
		}
	}
	if (IsDashAnimation)
	{
		if (PlayerControllerRef)
		{
			GetOwner()->DisableInput(PlayerControllerRef);
		}
		APFUnrealCharacter* PlayerRef = Cast<APFUnrealCharacter>(Cast<APawn>(GetOwner()));
		if (PlayerRef)
		{
			PlayerRef->GetCharacterMovement()->DisableMovement();
			PlayerRef->OnDashStart.Broadcast();
		}
		IsDashing = true;
		return;
	}
	else
	{
		GetOwner()->SetActorLocation(StartLocation + ForwardDirection * DDistance);
	}
}

void UDashComponent::LerpPlayer(float DeltaTime)
{
	float Angle;

	Angle = FMath::DegreesToRadians(FMath::Lerp(DashDegree, 0.f, CurrentAlpha));

	float SinValue;
	float CosValue;

	FMath::SinCos(&SinValue, &CosValue, Angle);

	FVector TargetLocation = GetDirection(CosValue, SinValue) + (StartLocation + ForwardDirection * (DDistance/2));
	GetOwner()->SetActorLocation(TargetLocation);
	if (CurrentAlpha >= 1.f)
	{
		CurrentAlpha = 0.f;
		if (PlayerControllerRef)
		{
			GetOwner()->EnableInput(PlayerControllerRef);
		}
		APFUnrealCharacter* PlayerRef = Cast<APFUnrealCharacter>(Cast<APawn>(GetOwner()));
		if (PlayerRef)
		{
			PlayerRef->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
			PlayerRef->OnDashEnd.Broadcast();
		}
		IsDashing = false;
		return;
	}
	CurrentAlpha += (1 / DashTime) * DeltaTime;

	// Pour éviter que ce soit décalé
	if (CurrentAlpha>=1.f)
	{
		CurrentAlpha = 1.f;
	}
	return;
}

