#pragma once
#include "CoreMinimal.h"
#include "GameData.generated.h"

USTRUCT(BlueprintType)
struct FDataGame
{
	GENERATED_BODY()

public:

	FDataGame(): PlayerName("None"){};

	FDataGame(FString _PlayerName, FTimespan _LevelChrono): PlayerName(_PlayerName), LevelChrono(_LevelChrono){};

	~FDataGame(){};

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString PlayerName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FTimespan LevelChrono;

};