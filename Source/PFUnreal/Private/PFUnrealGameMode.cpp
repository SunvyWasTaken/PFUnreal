// Copyright Epic Games, Inc. All Rights Reserved.

#include "../PFUnrealGameMode.h"
#include "../PFUnrealCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "../Widget/WLevelFinish.h"
#include "../GI_PGUnreal.h"

APFUnrealGameMode::APFUnrealGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void APFUnrealGameMode::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(FTimerLevel, this, &APFUnrealGameMode::TimeLevel, 0.333f, true);
	APFUnrealCharacter* CharacterRef = Cast<APFUnrealCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (CharacterRef)
	{
		CharacterRef->OnPlayerDeath.AddDynamic(this, &APFUnrealGameMode::RestartLevel);
	}
}

void APFUnrealGameMode::TimeLevel()
{
	CurrentTime += 333.f;
	//FTimespan TimeInSec = FTimespan::FromMilliseconds(CurrentTime);
	//UE_LOG(LogTemp, Warning, TEXT("Actual Time %f s"), TimeInSec.GetTotalSeconds());
}

void APFUnrealGameMode::RestartLevel()
{
	UE_LOG(LogTemp, Warning, TEXT("Je restart?"));
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), GetWorld()->GetCurrentLevel());
	return;
}

void APFUnrealGameMode::DisplayEndScreen()
{
	UE_LOG(LogTemp, Warning, TEXT("End Screen"));
	GetWorld()->GetTimerManager().PauseTimer(FTimerLevel);
	GetWorld()->GetTimerManager().ClearTimer(FTimerLevel);



	if (EndScreen)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		UWLevelFinish* LevelFinishWidgetRef = Cast<UWLevelFinish>(CreateWidget(PlayerController, EndScreen));
		LevelFinishWidgetRef->WidgetTime = FTimespan::FromMilliseconds(CurrentTime);
		LevelFinishWidgetRef->AddToViewport();
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController, LevelFinishWidgetRef);
		PlayerController->SetShowMouseCursor(true);
	}
}

void APFUnrealGameMode::GoToMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), "L_Menu");
	return;
}

