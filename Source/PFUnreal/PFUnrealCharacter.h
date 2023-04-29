// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PFUnrealCharacter.generated.h"



UCLASS(config=Game)
class APFUnrealCharacter : public ACharacter
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTakeDamage, int, value);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDashStart);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDashEnd);

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* PauseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* DashAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AutoAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom|Components", meta = (AllowPrivateAccess = "true"))
	class UDashComponent* DashCompo;


public:

	APFUnrealCharacter();

	virtual void Tick( float DeltaSeconds );

	virtual void FellOutOfWorld(const class UDamageType& dmgType) override;

	UPROPERTY(EditDefaultsOnly, Meta = (DisplayName = "Widget In Game"), Category = "Custom|Widget")
	/// <summary>
	/// Reference de la class Widget à faire afficher à l'écran pendant la partie.
	/// </summary>
	TSubclassOf<UUserWidget> WidgetInGameClass;
	
	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "Widget In Pause"), Category = "Custom|Widget")
	/// <summary>
	/// Class du widget qui sera afficher lors que le jeu sera mis en pause depuis le toggle pause.
	/// </summary>
	TSubclassOf<UUserWidget> WidgetInPauseClass;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "Class AI Ally"), Category = "Custom|AI")
	TSubclassOf<class AAIController> AllyControllerClass;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "Class Camera Spec"), Category = "Custom|AI")
	TSubclassOf<APawn> CameraSpec;	

	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "Hauteur de la Camera"), Category = "Custom|Camera")
	/// <summary>
	/// Hauteur de la camera relatif à la position inital du joueur.
	/// </summary>
	float CameraHeight = 500.f;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "Camera Back"), Category = "Custom|Camera")
	/// <summary>
	/// Distance arriere entre le player et la camera
	/// </summary>
	float CameraBack = 500.f;

	UPROPERTY(EditDefaultsOnly, Meta=(DisplayName ="Nombre de vie", ClampMin = 1, ClampMax = 10, UIMin = 1, UIMax = 10), Category = "Custom|PlayerData")
	/// <summary>
	/// Nombre de vie du joueur.
	/// </summary>
	int NbrHeart = 3;

	UPROPERTY(BlueprintAssignable)
	/// <summary>
	/// Delegate Call a chaque fois que le joueur perd un coeur.
	/// </summary>
	FOnTakeDamage OnTakeDamage;

	UPROPERTY(BlueprintAssignable)
	/// <summary>
	/// Delegate call lorsque le joueur n'as plus de point de vie.
	/// </summary>
	FOnDeath OnPlayerDeath;

	UPROPERTY(BlueprintAssignable)
	FOnDashStart OnDashStart;

	UPROPERTY(BlueprintAssignable)
	FOnDashEnd OnDashEnd;

	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// A call lorsque le joueur reçoit des damages.
	/// </summary>
	void ApplyDamage();

	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// Juste une fonction Test pour savoir si je peux bien augmenté et réduire la vie
	/// </summary>
	/// <param name="value">Mettre 1 ou -1</param>
	void TestDamage(int value);

	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// Fonction à call pour pause et unpause et affiche le menu select dans le "Widget in Pause"
	/// </summary>
	void TogglePause();

	UFUNCTION(BlueprintCallable)
	void Dash(const FInputActionValue& value);

	UFUNCTION(BlueprintCallable)
	void AutoWin();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	UPROPERTY()
	/// <summary>
	/// Garde en mémoire la location du joueur lorsqu'il a commencer à ne pas changer en partie
	/// </summary>
	FVector StartLocation;

	int NbrMaxHeart;

	class UWPause* PauseMenuRef = nullptr;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

