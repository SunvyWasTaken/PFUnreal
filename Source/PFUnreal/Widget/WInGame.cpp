// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "WInGame.h"
#include "../PFUnrealCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "WHeart.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "../PFUnrealGameMode.h"


void UWInGame::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	GameModeRef = Cast<APFUnrealGameMode>(GetWorld()->GetAuthGameMode());
	if (!GameModeRef)
	{
		UE_LOG(LogTemp, Warning, TEXT("The wrong game mode is set on the map"));
		return;
	}
	APFUnrealCharacter* PlayerRef = Cast<APFUnrealCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!PlayerRef)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cast du player fail lors de l'init du widget in game"));
		return;
	}
	NbrHeart = PlayerRef->NbrHeart;
	PlayerRef->OnTakeDamage.AddDynamic(this, &UWInGame::SetHeart);
	for (int i = 0; i < NbrHeart; ++i)
	{
		UWHeart* CurrentHeart = Cast<UWHeart>(CreateWidget(this, WidgetHeart));
		UHorizontalBoxSlot* CurrentSlot = HeartBox->AddChildToHorizontalBox(CurrentHeart);
		CurrentSlot->SetPadding(HeartPadding);
		CurrentHeart->ChangeHeart(1);
	}
	return;
}

void UWInGame::SetHeart(int value)
{
	// Call lorsque le joueur gagne de la vie
	if (value > NbrHeart && value - 1 <= HeartBox->GetChildrenCount() - 1)
	{
		UWHeart* CurrentHeart = Cast<UWHeart>(HeartBox->GetChildAt(value - 1));
		CurrentHeart->ChangeHeart(value - NbrHeart);
	}
	else if (value >= 0 && value <= HeartBox->GetChildrenCount() - 1)
	{
		UWHeart* CurrentHeart = Cast<UWHeart>(HeartBox->GetChildAt(value));
		CurrentHeart->ChangeHeart(value - NbrHeart);
	}
	NbrHeart = value;
	return;
}
