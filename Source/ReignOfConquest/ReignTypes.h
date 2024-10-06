#pragma once

#include "ReignTypes.generated.h"

USTRUCT(BlueprintType)
struct FInteractedInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString Name;
};


UENUM(BlueprintType)
enum class EReignMouseCursor : uint8
{
	Default = 0 UMETA(DisplayName = "Normal"),
	Attack,
	Dead,
	GuiAct,
	ItemGive,
	ItemPickup,
	Move,
	Portal,
	Talk,
	Resize,
	TargetFriendly,
	TargetUnfriendly,
	UnfriendlyAttack,
	Zoom
};