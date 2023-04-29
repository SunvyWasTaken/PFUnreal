#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameData.h"
#include "SaveMain.generated.h"

UCLASS()
class PFUNREAL_API USaveMain : public USaveGame
{
	GENERATED_BODY()

public:
	// Définit les valeurs par défaut des propriétés de ce empty
	USaveMain();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FString, FDataGame> Levels;
	

};
