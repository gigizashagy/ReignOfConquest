#pragma once
#include "CoreMinimal.h"
#include "InteractionInterface.generated.h"

UENUM(BlueprintType)
enum class EInteractionRelation : uint8
{
	Neutral = 0,
	Alies,
	Hostile
};

UENUM(BlueprintType)
enum class EInteractionType : uint8
{
	PickUp,
	Character
};

UINTERFACE(meta=(CannotImplementInterfaceInBlueprint))
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

class IInteractionInterface
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	virtual EInteractionType GetInteractionType() const = 0;

	UFUNCTION(BlueprintCallable)
	virtual EInteractionRelation GetInteractionRelation() const = 0;

	// Can this object even be attacked
	UFUNCTION(BlueprintCallable)
	virtual bool CanEvenAttack() const = 0;

	// For NPC speak behaviour
	UFUNCTION(BlueprintCallable)
	virtual bool CanInteract() const = 0;
};