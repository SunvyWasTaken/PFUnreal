// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WPause.generated.h"

/**
 * 
 */
UCLASS()
class PFUNREAL_API UWPause : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeOnInitialized();

public:

	UPROPERTY(meta = (BindWidget))
	class UButton* BRestart;

	UFUNCTION(BlueprintNativeEvent)
	void EnableAWidget();

	UFUNCTION(BlueprintCallable)
	void RestartOui();

	
};
