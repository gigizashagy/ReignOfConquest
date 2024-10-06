#pragma once

#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

class AReignPlayerController;
class IInteractionInterface;
class UInputAction;
class UInputComponent;
struct FInputActionValue;
enum class EReignMouseCursor : uint8;

UCLASS()
class UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UInteractionComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetupInputComponent(UInputComponent* PlayerInputComponent);

	static void SetHoveredActor(AActor* Actor, UMaterialInstanceDynamic* OutlineMaterial);
	static void SetUseOutlineActor(AActor* Actor, bool bUseOutline);

	void SetHoverActor(AActor* Actor);
	void SetInteractActor(AActor* Actor);
	void ClearInteractActor();
	
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void Select(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void ConfirmSelection(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	AReignPlayerController* GetPlayerController() const;

	EReignMouseCursor GetCursorTypeForActor(AActor* Actor) const;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* SelectAction = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ConfirmSelectionAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstance* HoveredMaterial = nullptr;
	UPROPERTY(Transient, BlueprintReadOnly)
	UMaterialInstanceDynamic* InstanceHoveredMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterialParameterCollection* OutlineParameters = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ECollisionChannel> TraceChannel;

	UPROPERTY(Transient)
	TObjectPtr<AReignPlayerController> PlayerController;

	//TScriptInterface<IInteractionInterface> TargetInteracted;
	TWeakObjectPtr<AActor> HoveredInteractedActor;
	TWeakObjectPtr<AActor> TargetInteractedActor;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite)
	uint8 bForceAttack:1 = false;

	uint8 bIsActive:1 = false;
	uint8 bOngoingSelection:1 = false;
};
