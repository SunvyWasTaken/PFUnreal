// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PFUnrealGameMode.generated.h"

UCLASS(minimalapi)
class APFUnrealGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APFUnrealGameMode();

protected:

	virtual void BeginPlay();

	FTimerHandle FTimerLevel;

	void TimeLevel();

	double CurrentTime;

public:

	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// Fonction à call pour relancer la map
	/// </summary>
	void RestartLevel();

	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// Fonction a call à la fin du niveau
	/// </summary>
	void DisplayEndScreen();

	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// Fonction à call pour retourner dans le menu principal.
	/// </summary>
	void GoToMenu();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (DisplayName = "Ecran de fin de niveau"), Category = "Custom|Widget")
	TSubclassOf<class UUserWidget> EndScreen;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Custom")
	FTimespan GetTime() { return FTimespan::FromMilliseconds(CurrentTime); };


};



