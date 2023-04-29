// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

class ACoin;

UCLASS()
class PFUNREAL_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* BodyComponent;

	UPROPERTY()
	class USceneComponent* DoorJoin;
	UPROPERTY()
	class USceneComponent* CustomRoot;

	UFUNCTION(BlueprintNativeEvent)
	/// <summary>
	/// Event Call lorsqu'il n'y a plus de coin dans le monde. à Override en blueprint 
	/// </summary>
	void OpenDoor();

	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// Fonction à call à chaque frame lerp entre 2 Rotation donner.
	/// </summary>
	/// <param name="CurrentRotation">A Rentré une valeur entre 0 et 1</param>
	void SetDoorRotation(float CurrentRotation);

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Angle d'ouverture de la porte", ClampMin = -90.f, ClampMax = 90.f, UIMin = -90.f, UIMax = 90.f), Category = "Custom|Property")
	/// <summary>
	/// Angle dans le quel la porte va s'ouvrir.
	/// </summary>
	float DoorAngle = -90.f;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|Property")
	/// <summary>
	/// Reference class Blueprint des coin dans le monde si il n'est pas set la porte ne va pas S'ouvrir.
	/// </summary>
	TSubclassOf<ACoin> CoinClass;

	UFUNCTION()
	/// <summary>
	/// Fonction à appeler à chaque fois qu'un coin est supprimer du monde.
	/// </summary>
	/// <param name="target"></param>
	void RemoveCoin(ACoin* target);

protected:

	UPROPERTY()
	/// <summary>
	/// Reference de tous les coins qui sont dans le level. à Set au begin play
	/// </summary>
	TArray<AActor*> TabCoinRef; 

};
