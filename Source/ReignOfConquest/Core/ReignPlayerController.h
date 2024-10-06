#pragma once

#include "GameFramework/PlayerController.h"
#include "CoreTypes.h"
#include "UI/ReignCursorWidget.h"
#include "ReignPlayerController.generated.h"

class UInteractionComponent;

UCLASS()
class AReignPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AReignPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	/** Allows the PlayerController to set up custom input bindings. */
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

	void SetMouseCursorType(EReignMouseCursor Type) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInteractionComponent> Interaction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftClassPtr<UReignCursorWidget> CursorWidgetClass;

	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UReignCursorWidget> CursorWidgetInstance;
};
