// Fill out your copyright notice in the Description page of Project Settings.


#include "WHeart.h"
#include "Components/Image.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UWHeart::ChangeHeart(int value)
{
	if (value > 0)
	{
		IHeart->SetBrush(UWidgetBlueprintLibrary::MakeBrushFromAsset(FullHeart));
	}
	else
	{
		IHeart->SetBrush(UWidgetBlueprintLibrary::MakeBrushFromAsset(EmptyHeart));
	}
}
