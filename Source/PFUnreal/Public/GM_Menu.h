// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GM_Menu.generated.h"

/**
 * 
 */
UCLASS()
class PFUNREAL_API AGM_Menu : public AGameModeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Custom|Property")
	TSubclassOf<UUserWidget> MenuClass;

protected:

	virtual void BeginPlay();
	
};
