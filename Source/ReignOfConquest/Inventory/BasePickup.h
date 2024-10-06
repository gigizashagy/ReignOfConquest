// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ReignOfConquest/Systems/Interaction/InteractionInterface.h"
#include "BasePickup.generated.h"

UCLASS()
class REIGNOFCONQUEST_API ABasePickup : public AActor, public IInteractionInterface
{
	GENERATED_BODY()

public:
	ABasePickup(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	// Begin InteractionInterface
	virtual EInteractionType GetInteractionType() const override { return EInteractionType::PickUp; }
	virtual EInteractionRelation GetInteractionRelation() const override { return EInteractionRelation::Alies; }
	virtual bool CanEvenAttack() const override { return false; }
	virtual bool CanInteract() const override { return false; }
	// End InteractionInterface

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> StaticMesh;
};
