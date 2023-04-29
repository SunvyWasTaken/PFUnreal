// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WInGame.generated.h"

/**
 * 
 */
UCLASS()
class PFUNREAL_API UWInGame : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeOnInitialized();

public:
	
	UPROPERTY(BlueprintReadOnly, Meta=(BindWidget))
	class UHorizontalBox* HeartBox;
	
	UPROPERTY(EditDefaultsOnly, Category = "Custom|Property")
	/// <summary>
	/// Class du widget heart qui sera display doit avoir une reference pour fonctionner
	/// </summary>
	TSubclassOf<UUserWidget> WidgetHeart;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|Property")
	/// <summary>
	/// Padding general entre chaque coeur et le haut et bas de l'horizontal box.
	/// </summary>
	float HeartPadding = 5.f;

	UPROPERTY(BlueprintReadOnly, Category = "Custom|Reference")
	class APFUnrealGameMode* GameModeRef;

private:

	UPROPERTY()
	/// <summary>
	/// Garde en tête la valeur avant l'actualisation à utiliser pour savoir si le joueur à gagner ou perdu en vie.
	/// </summary>
	int NbrHeart;

	UFUNCTION()
	/// <summary>
	/// Call lorsque la vie du joueur change
	/// Ne faire que des changements de 1 en 1 sinon ce sera casser.
	/// </summary>
	/// <param name="value">Mettre la valeur actuelle du joueur</param>
	void SetHeart(int value);

};
