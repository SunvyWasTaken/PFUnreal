// Copyright Epic Games, Inc. All Rights Reserved.

#include "../PFUnrealCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "../Widget/WPause.h"
#include "../PFUnrealGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "DashComponent.h"
#include "../SpecPawn.h"
#include "AIController.h"


//////////////////////////////////////////////////////////////////////////
// APFUnrealCharacter

APFUnrealCharacter::APFUnrealCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	FollowCamera->SetWorldRotation(FRotator(-45.f,0.f,0.f));

	DashCompo = CreateDefaultSubobject<UDashComponent>(TEXT("DashCompo"));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void APFUnrealCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const FVector TargetCamLocation = FVector(GetActorLocation().X - CameraBack, GetActorLocation().Y, StartLocation.Z + CameraHeight);
	FollowCamera->SetWorldLocation(TargetCamLocation);
}

void APFUnrealCharacter::FellOutOfWorld(const UDamageType& dmgType)
{
	ApplyDamage();
	return;
}

void APFUnrealCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	NbrMaxHeart = NbrHeart;

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	// Creation du widget + affichage à l'écran.
	if (WidgetInGameClass)
	{
		if(APlayerController* PlayerController = Cast<APlayerController>(Controller))
		{
			UUserWidget* InGameWidget = Cast<UUserWidget>(CreateWidget(PlayerController, WidgetInGameClass));
			InGameWidget->AddToViewport();
			PlayerController->SetShowMouseCursor(false);
			PlayerController->SetInputMode(FInputModeGameOnly());
		}
	}

	StartLocation = GetActorLocation();
}

//////////////////////////////////////////////////////////////////////////
// Input

void APFUnrealCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		////Jumping
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APFUnrealCharacter::Move);

		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &APFUnrealCharacter::TogglePause);

		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Triggered, this, &APFUnrealCharacter::Dash);

		EnhancedInputComponent->BindAction(AutoAction, ETriggerEvent::Triggered, this, &APFUnrealCharacter::AutoWin);

	}

}

void APFUnrealCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APFUnrealCharacter::ApplyDamage()
{
	--NbrHeart;
	if (NbrHeart <= 0)
	{
		NbrHeart = 0;
		// je call à la main parce que de base je voulais utilisé mon delegate mais j'arrivais pas à le bind en runtime.
		//Cast<APFUnrealGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->RestartLevel();
		OnPlayerDeath.Broadcast();
	}
	else
	{
		SetActorLocation(StartLocation, false, nullptr, ETeleportType::ResetPhysics);
	}
	OnTakeDamage.Broadcast(NbrHeart);
	return;
}

void APFUnrealCharacter::TestDamage(int value = -1)
{
	NbrHeart += value;
	if (NbrHeart <= 0)
	{
		NbrHeart = 0;
	}
	else if(NbrHeart >= NbrMaxHeart)
	{
		NbrHeart = NbrMaxHeart;
	}
	OnTakeDamage.Broadcast(NbrHeart);
	return;
}

void APFUnrealCharacter::TogglePause()
{
	APlayerController* PlayerControllerRef = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (UGameplayStatics::IsGamePaused(GetWorld()))
	{
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		if (PauseMenuRef)
		{
			PauseMenuRef->SetVisibility(ESlateVisibility::Collapsed);
			PlayerControllerRef->SetShowMouseCursor(false);
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerControllerRef);
		}
	}
	else
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		if (PauseMenuRef)
		{
			PauseMenuRef->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
		else
		{
			if (WidgetInPauseClass)
			{
				PauseMenuRef = Cast<UWPause>(CreateWidget(PlayerControllerRef, WidgetInPauseClass));
				if (!PauseMenuRef)
				{
					return;
				}
				PauseMenuRef->AddToViewport();
			}
			else
			{
				return;
			}
		}
		PauseMenuRef->EnableAWidget();
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerControllerRef, PauseMenuRef);
		PlayerControllerRef->SetShowMouseCursor(true);
	}
}

void APFUnrealCharacter::AutoWin()
{
	if (CameraSpec)
	{
		ASpecPawn* CameraRef = GetWorld()->SpawnActor<ASpecPawn>(CameraSpec, FVector(0.f), FRotator(-45.f, 0.f, 0.f));
		CameraRef->PlayerRef = this;
		GetController()->Possess(CameraRef);
		CameraRef->AttachToComponent(FollowCamera, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
	if (AllyControllerClass)
	{
		AAIController* ControllerAIRef = GetWorld()->SpawnActor<AAIController>(AllyControllerClass);
		ControllerAIRef->Possess(this);
	}
}

void APFUnrealCharacter::Dash(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Warning, TEXT("Dash!!!"));
	DashCompo->Dash(value.Get<float>() > 0);
}

