#include "SpecPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PFUnrealCharacter.h"

// Définit les valeurs par défaut
ASpecPawn::ASpecPawn()
{
	// Définissez ce pawn pour appeler Tick() à chaque frame. Vous pouvez désactiver cette option pour améliorer les performances si vous n’en avez pas besoin.
	PrimaryActorTick.bCanEverTick = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	RootComponent = FollowCamera;
}

void ASpecPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &ASpecPawn::Pause);
	}
}

void ASpecPawn::Pause()
{
	if (PlayerRef)
	{
		PlayerRef->TogglePause();
	}
}
