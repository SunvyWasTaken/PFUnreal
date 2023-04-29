#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameData.h"
#include "GI_PGUnreal.generated.h"

UCLASS()
class PFUNREAL_API UGI_PGUnreal : public UGameInstance
{
	GENERATED_BODY()

public:

	// Définit les valeurs par défaut des propriétés de ce empty
	UGI_PGUnreal();

	UFUNCTION()
	void Init();

	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// Fonction à call pour récup la save dans les dossiers.
	/// Si il n'y a pas de fichier save creat un nouveau fichier save.
	/// </summary>
	void FGetSaveMain();

	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// Fonction à call pour récup les data save.
	/// Override les data en cours.
	/// </summary>
	void FLoadData();

	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// Fonction à call pour save les data
	/// les avoir set au préalable
	/// </summary>
	void FSaveData();

	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// Delete all the save from the computer
	/// </summary>
	void DeleteSave();

	UFUNCTION(BlueprintCallable)
	void UpdateData(FString& LevelName, FDataGame& NewDataGame);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category	= "Custom|Main")
	FString SaveNameMain = "OuiSave";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Custom|Save")
	TSubclassOf<class USaveGame> SaveClass;

	UPROPERTY()
	class USaveMain* SaveGameMainRef;

	UPROPERTY(BlueprintReadWrite, Category = "Custom|Map")
	TMap<FString, FDataGame> Levels;

	UFUNCTION(BlueprintCallable)
	void NextMap();

};
