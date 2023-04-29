// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "WPause.h"
#include "Components/Button.h"
#include "../PFUnrealGamemode.h"

void UWPause::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	UE_LOG(LogTemp, Warning, TEXT("Création du pause"));
	//BRestart->OnPressed.AddDynamic(this, &UWPause::RestartOui);
	BRestart->OnClicked.AddDynamic(this, &UWPause::RestartOui);
	return;
}

void UWPause::EnableAWidget_Implementation()
{
}

void UWPause::RestartOui()
{
	UE_LOG(LogTemp, Warning, TEXT("Tu Press bien le button je t'assure"));
	APFUnrealGameMode* GameMmodeRef = Cast<APFUnrealGameMode>(GetWorld()->GetAuthGameMode());
	GameMmodeRef->RestartLevel();
	return;
}
