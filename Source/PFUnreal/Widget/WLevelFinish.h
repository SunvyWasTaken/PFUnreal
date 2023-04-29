// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WLevelFinish.generated.h"

/**
 * 
 */
UCLASS()
class PFUNREAL_API UWLevelFinish : public UUserWidget
{
	GENERATED_BODY()

	virtual bool Initialize();
	
public:

	virtual void NativeOnInitialized();

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* BRetry;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* BMenu;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* BNext;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UEditableTextBox* ETBNewName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FTimespan WidgetTime;

	UPROPERTY(BlueprintReadOnly)
	FTimespan BestTime;

	UPROPERTY(BlueprintReadOnly, Category = "Custom")
	bool IsNewBest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	FText DefaultName;

	UFUNCTION(BlueprintCallable)
	void Restart();

	UFUNCTION(BlueprintCallable)
	void ToMenu();

	UFUNCTION()
	void ToNext();

	UFUNCTION()
	void SetNameForRecord(const FText& Text, ETextCommit::Type CommitMethod);

private:

	UFUNCTION()
	void SetBestGame(class UGI_PGUnreal* GameInstanceRef, const FText& Text, FString CurrentLevelName);

	UFUNCTION()
	void CheckBestGame(const FText& Text);


};
