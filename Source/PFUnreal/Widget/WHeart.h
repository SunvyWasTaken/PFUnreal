// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
//#include "Styling/SlateBrush.h"
#include "WHeart.generated.h"

/**
 * 
 */
UCLASS()
class PFUNREAL_API UWHeart : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION()
	/// <summary>
	/// A call pour modifier le coeur
	/// </summary>
	/// <param name="value">Valeur Negatif pour le desactiver et valeur positif pour l'activer</param>
	void ChangeHeart(int value);
	
	UPROPERTY(Meta=(BindWidget))
	class UImage* IHeart;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|Property")
	/// <summary>
	/// Reference SlateBrush pour lorsque la vie est pleine
	/// </summary>
	class USlateBrushAsset* FullHeart;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|Property")
	/// <summary>
	/// Reference lorsque la vie est vide.
	/// </summary>
	class USlateBrushAsset* EmptyHeart;
	
};
