#pragma once

#include "GameFramework/GameModeBase.h"
#include "ReignGameMode.generated.h"

UCLASS()
class AReignGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AReignGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
