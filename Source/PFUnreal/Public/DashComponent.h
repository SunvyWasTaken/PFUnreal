// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DashComponent.generated.h"

// 2 dash disponible en demi cercle.
UCLASS( ClassGroup=(Movement), meta=(BlueprintSpawnableComponent, DisplayName = "Dash Movement"))
class PFUNREAL_API UDashComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDashComponent();

protected:

	virtual void BeginPlay();

public:	

	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);

	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// Fonction à call pour que le character Dash en arc de cercle
	/// </summary>
	/// <param name="IsLeft">Vrai pour faire un arc sur la Gauche, faux pour la Droite</param>
	void Dash(bool IsLeft);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Dash Distance"), Category = "Property")
	/// <summary>
	/// Distance du Dash
	/// </summary>
	float DDistance = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Nombre de division", ClampMin = 1, UIMin = 1), Category = "Property")
	/// <summary>
	/// Nombre de division pour le calcule des collisions lors du dash plus c'est haut plus c'est precis et laggy
	/// </summary>
	int DDivision = 6;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Is Dash Animation"), Category = "Property")
	/// <summary>
	/// Es que le dash doit etre animer???
	/// Si faux dash sera Instant
	/// Si vrai il y aura un temps au dash.
	/// </summary>
	bool IsDashAnimation = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Temps du Dash", EditCondition = IsDashAnimation, ClampMin = 0.f, UIMin = 0.f), AdvancedDisplay, Category = "Property")
	/// <summary>
	/// Temps du Dash si il y a une animation
	/// Si il n'y a pas d'animation le dash sera instantane.
	/// </summary>
	float DashTime = 1.f;

	/// <summary>
	/// Distortion du dash
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Distortion Du Dash", EditCondition = IsDashAnimation, ClampMin = 0.01f, UIMin = 0.01f, ClampMax = 10.f, UIMax = 10.f), AdvancedDisplay, Category = "Property")
	float DashDistorsion = 1.f;


protected:
	
	// je voulais le mettre en param mais ça casse tous mes mat donc....
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Degree Du Dash", EditCondition = IsDashAnimation, ClampMin = 0.f, UIMin = 0.f, ClampMax = 360.f, UIMax = 360.f), AdvancedDisplay, Category = "Property")
	const float DashDegree = 180.f;

	// Timer Handler du dash
	bool IsDashing = false;

	// Alpha actuel pour que dans ma boucle ce soit bien.
	float CurrentAlpha = 0.f;

	// Location de depart du dash.
	FVector StartLocation;

	// Direction vers la quel le joueur regarde.
	FVector ForwardDirection;

	// Direction de vector droit 
	FVector RightDirection;

	// Reference du player controller de l'owner
	class APlayerController* PlayerControllerRef;

	// Fonction appeler dans un timer pour l'animation
	// Je voulais pas le tick
	void LerpPlayer(float DeltaTime);

	// les differents point en fonction du cos et du sin
	FVector GetDirection(float Cos, float Sin);

		
};
