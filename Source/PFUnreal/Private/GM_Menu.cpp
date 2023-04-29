// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_Menu.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void AGM_Menu::BeginPlay()
{
	Super::BeginPlay();
	if (MenuClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Creation du widget."));
		APlayerController* PlayerControllerRef = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		UUserWidget* CurrentWidget = Cast<UUserWidget>(CreateWidget(PlayerControllerRef, MenuClass));
		CurrentWidget->AddToViewport();
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerControllerRef, CurrentWidget);
		PlayerControllerRef->SetShowMouseCursor(true);
	}
}
