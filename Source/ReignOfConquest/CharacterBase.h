#pragma once

#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class UInputAction;
struct FInputActionValue;

//TODO: separate to player character
UCLASS()
class ACharacterBase : public ACharacter
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
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* Camera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* HoldLookAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	uint8 bHoldLook : 1;
};
