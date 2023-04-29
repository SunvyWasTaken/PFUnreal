#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "SpecPawn.generated.h"

UCLASS()
class PFUNREAL_API ASpecPawn : public APawn
{
	GENERATED_BODY()

public:
	// Définit les valeurs par défaut des propriétés de ce pawn
	ASpecPawn();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* FollowCamera;

	UPROPERTY(BlueprintReadOnly, Category = "Custom")
	class APFUnrealCharacter* PlayerRef;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* PauseAction;

	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

	void Pause();

};
