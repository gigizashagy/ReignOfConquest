#pragma once

#include "GameFramework/Character.h"
#include "ReignOfConquest/Systems/Interaction/InteractionInterface.h"
#include "CharacterBase.generated.h"

class UInputAction;
struct FInputActionValue;

//TODO: separate to player character
UCLASS()
class ACharacterBase : public ACharacter, public IInteractionInterface
{
	GENERATED_BODY()
public:
	ACharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category = "Character Base")
	APlayerController* GetPlayerController() const;
protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Character Base")
	void Move(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Character Base")
	void Look(const FInputActionValue& Value);

	UFUNCTION(BlueprintNativeEvent, Category = "Character Base")
	void HoldLook(const FInputActionValue& Value);

	// Begin InteractionInterface
	virtual EInteractionType GetInteractionType() const override { return EInteractionType::Character; }
	virtual EInteractionRelation GetInteractionRelation() const override { return  bHostile ? EInteractionRelation::Hostile : bIsNPC ? EInteractionRelation::Neutral : EInteractionRelation::Alies; }
	virtual bool CanEvenAttack() const override { return true; }
	virtual bool CanInteract() const override { return true; }
	// End InteractionInterface

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class USpringArmComponent> CameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class UCameraComponent> Camera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* HoldLookAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	uint8 bHoldLook : 1 = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Base")
	uint8 bIsNPC : 1 = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Base", meta=(EditCondition="bIsNPC == false"))
	uint8 bHostile : 1 = false;
};
