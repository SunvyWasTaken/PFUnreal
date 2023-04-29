#include "GI_PGUnreal.h"
#include "Kismet/GameplayStatics.h"
#include "SaveMain.h"

// Définit les valeurs par défaut
UGI_PGUnreal::UGI_PGUnreal()
{

}

void UGI_PGUnreal::Init()
{
	Super::Init();
	FGetSaveMain();
	FLoadData();
}

void UGI_PGUnreal::FGetSaveMain()
{
	if (UGameplayStatics::DoesSaveGameExist(SaveNameMain, 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("Recup de l'ancienne save"));
		SaveGameMainRef = Cast<USaveMain>(UGameplayStatics::LoadGameFromSlot(SaveNameMain, 0));
		return;
	}
	else
	{
		if (SaveClass)
		{
			UE_LOG(LogTemp, Warning, TEXT("Creation d'une nouvelle save"));
			SaveGameMainRef = Cast<USaveMain>(UGameplayStatics::CreateSaveGameObject(SaveClass));
			UGameplayStatics::SaveGameToSlot(Cast<USaveGame>(SaveGameMainRef), SaveNameMain, 0);
		}
	}
}

void UGI_PGUnreal::FLoadData()
{
	UE_LOG(LogTemp, Warning, TEXT("Set de Map"));
	Levels = SaveGameMainRef->Levels;
}

void UGI_PGUnreal::FSaveData()
{
	if (SaveGameMainRef)
	{
		UE_LOG(LogTemp, Warning, TEXT("Save Effectuer"));
		UGameplayStatics::SaveGameToSlot(SaveGameMainRef, SaveNameMain, 0);
	}
}

void UGI_PGUnreal::DeleteSave()
{
	SaveGameMainRef = Cast<USaveMain>(UGameplayStatics::CreateSaveGameObject(SaveClass));
	UGameplayStatics::DeleteGameInSlot(SaveNameMain, 0);
	return;
}

void UGI_PGUnreal::UpdateData(FString& LevelName, FDataGame& NewDataGame)
{
	if (!Levels.Contains(LevelName))
		Levels.Add(LevelName, NewDataGame);
	else
		Levels[LevelName] = NewDataGame;
	FSaveData();
	return;
}

void UGI_PGUnreal::NextMap()
{
	FString CurrentLevel = GetWorld()->GetMapName();
	if (CurrentLevel == "L_Level1" || CurrentLevel == "UEDPIE_0_L_Level1")
	{ 
		UGameplayStatics::OpenLevel(GetWorld(), "L_Level2");
		return;
	}
	else if (CurrentLevel == "L_Level2" || CurrentLevel == "UEDPIE_0_L_Level2")
	{ 
		UGameplayStatics::OpenLevel(GetWorld(), "L_Level3");
		return;
	}
	else if (CurrentLevel == "L_Level3" || CurrentLevel == "UEDPIE_0_L_Level3")
	{
		UGameplayStatics::OpenLevel(GetWorld(), "L_Menu");
		return;
	}
}

