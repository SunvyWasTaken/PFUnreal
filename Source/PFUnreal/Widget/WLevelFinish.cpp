// Fill out your copyright notice in the Description page of Project Settings.


#include "WLevelFinish.h"
#include "../PFUnrealGameMode.h"
#include "Components/Button.h"
#include "../GI_PGUnreal.h"
#include "Components/EditableTextBox.h"

bool UWLevelFinish::Initialize()
{
	Super::Initialize();
	DefaultName = FText::FromString("Player");
	return true;
}

void UWLevelFinish::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	UE_LOG(LogTemp, Warning, TEXT("Level finish bind"));
	BRetry->OnClicked.AddDynamic(this, &UWLevelFinish::Restart);
	BMenu->OnClicked.AddDynamic(this, &UWLevelFinish::ToMenu);
	BNext->OnClicked.AddDynamic(this, &UWLevelFinish::ToNext);
	ETBNewName->OnTextCommitted.AddDynamic(this, &UWLevelFinish::SetNameForRecord);

	UGI_PGUnreal* GameInstanceRef = Cast<UGI_PGUnreal>(GetWorld()->GetGameInstance());
	FString CurrentLevelName = GetWorld()->GetMapName();
	FDataGame* BestGame = GameInstanceRef->Levels.Find(CurrentLevelName);
	IsNewBest = false;
	if (BestGame)
	{
		BestTime = BestGame->LevelChrono;
		IsNewBest = WidgetTime < BestTime;
	}
	else
		IsNewBest = true;

	return;
}

void UWLevelFinish::Restart()
{
	APFUnrealGameMode* GameModeRef = Cast<APFUnrealGameMode>(GetWorld()->GetAuthGameMode());
	CheckBestGame(DefaultName);
	GameModeRef->RestartLevel();
	return;
}

void UWLevelFinish::ToMenu()
{
	APFUnrealGameMode* GameModeRef = Cast<APFUnrealGameMode>(GetWorld()->GetAuthGameMode());
	CheckBestGame(DefaultName);
	GameModeRef->GoToMenu();
	return;
}

void UWLevelFinish::ToNext()
{
	UGI_PGUnreal* GameInstanceRef = Cast<UGI_PGUnreal>(GetWorld()->GetGameInstance());
	CheckBestGame(DefaultName);
	GameInstanceRef->NextMap();
	return;
}

void UWLevelFinish::SetNameForRecord(const FText& Text, ETextCommit::Type CommitMethod)
{
	UE_LOG(LogTemp, Warning, TEXT("Yes name %s"), *Text.ToString());
	if (Text.IsEmpty())
	{
		CheckBestGame(DefaultName);
		return;
	}
	CheckBestGame(Text);
}

void UWLevelFinish::SetBestGame(UGI_PGUnreal* GameInstanceRef, const FText& Text, FString CurrentLevelName)
{
	UE_LOG(LogTemp, Warning, TEXT("Currently setting the new high score"));
	FDataGame NewRecord = FDataGame(Text.ToString(), WidgetTime);
	GameInstanceRef->UpdateData(CurrentLevelName, NewRecord);
	return;
}

void UWLevelFinish::CheckBestGame(const FText& Text)
{
	UGI_PGUnreal* GameInstanceRef = Cast<UGI_PGUnreal>(GetWorld()->GetGameInstance());
	if (GameInstanceRef)
	{
		FString CurrentLevelName = GetWorld()->GetMapName();
		FDataGame* BestGame = GameInstanceRef->Levels.Find(CurrentLevelName);
		if (BestGame)
		{
			if (BestGame->PlayerName != "None")
			{
				if (BestGame->LevelChrono.GetTotalMilliseconds() > WidgetTime.GetTotalMilliseconds())
				{
					UE_LOG(LogTemp, Warning, TEXT("New Record!!!"));
					SetBestGame(GameInstanceRef, Text, CurrentLevelName);
					return;
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Set directement le nouveau Time!!!"));
				SetBestGame(GameInstanceRef, Text, CurrentLevelName);
				return;
			}
		}
		else
		{
			SetBestGame(GameInstanceRef, Text, CurrentLevelName);
			return;
		}
	}
}
