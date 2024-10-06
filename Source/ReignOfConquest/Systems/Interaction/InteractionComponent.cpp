#include "InteractionComponent.h"

#include "EnhancedInputComponent.h"
#include "InteractionInterface.h"
#include "Core/ReignPlayerController.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Materials/MaterialParameterCollectionInstance.h"

static const FLinearColor NPCTargetColor = FLinearColor::Green;
static const FLinearColor AliesTargetColor = FLinearColor::Blue;
static const FLinearColor HostileTargetColor = FLinearColor::Red;
static const FLinearColor HoverTargetColor = FLinearColor::White;

static const FLinearColor SelectionOverlayColors[] =
{
	FLinearColor::Green, // Neutral = 0
	FLinearColor::Blue,  // Alies
	FLinearColor::Red    // Hostile
};

UInteractionComponent::UInteractionComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = GetOwner<AReignPlayerController>();
	InstanceHoveredMaterial = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), HoveredMaterial);

	ensure(InstanceHoveredMaterial);
	ensure(PlayerController);
}

void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	constexpr float TraceLength = 10000.0f;
	FVector Position, Direction;
	PlayerController->DeprojectMousePositionToWorld(Position, Direction);
	const FVector StartTrace = PlayerController->PlayerCameraManager->GetCameraLocation();
	const FVector EndTrace = StartTrace + (Direction * TraceLength);

	FCollisionQueryParams HitQueryParams;
	HitQueryParams.TraceTag = FName(TEXT("Interaction"));
	HitQueryParams.AddIgnoredActor(PlayerController->GetPawnOrSpectator());

	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, TraceChannel, HitQueryParams))
	{
		// Have Smth
		AActor* HitActor = HitResult.GetActor();

		if (HitActor && HitActor->Implements<UInteractionInterface>())
		{
			if (HitActor == HoveredInteractedActor)
				return;

				// Fill outline Selection
				SetHoverActor(HitActor);
		}
		else
		{
			SetHoverActor(nullptr);
		}
	}
	else
	{
		SetHoverActor(nullptr);
	}

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInteractionComponent::SetupInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Started, this, &UInteractionComponent::Select);
		//EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Completed, this, &UInteractionComponent::Select);
		EnhancedInputComponent->BindAction(ConfirmSelectionAction, ETriggerEvent::Started, this, &UInteractionComponent::ConfirmSelection);
	}
}

void UInteractionComponent::SetHoveredActor(AActor* Actor, UMaterialInstanceDynamic* OutlineMaterial)
{
	if (Actor)
	{
		if (UMeshComponent* Primitive = Cast<UMeshComponent>(Actor->GetRootComponent()))
		{
			Primitive->SetOverlayMaterial(OutlineMaterial);
		}
		else if (ACharacter* Character = Cast<ACharacter>(Actor))
		{
			USkeletalMeshComponent* Mesh = Character->GetMesh();
			Mesh->SetOverlayMaterial(OutlineMaterial);
		}
	}
}

void UInteractionComponent::SetUseOutlineActor(AActor* Actor, bool bUseOutline)
{
	if (Actor)
	{
		if (UMeshComponent* Primitive = Cast<UMeshComponent>(Actor->GetRootComponent()))
		{
			Primitive->SetRenderCustomDepth(bUseOutline);
		}
		else if (ACharacter* Character = Cast<ACharacter>(Actor))
		{
			USkeletalMeshComponent* Mesh = Character->GetMesh();
			Mesh->SetRenderCustomDepth(bUseOutline);
		}
	}
}

void UInteractionComponent::SetHoverActor(AActor* Actor)
{
	// Remove old actor outline
	if (HoveredInteractedActor.Get())
	{
		SetHoveredActor(HoveredInteractedActor.Get(), nullptr);
		HoveredInteractedActor.Reset();
		PlayerController->SetMouseCursorType(EReignMouseCursor::Default);
	}

	if (Actor)
	{
		HoveredInteractedActor = Actor;
		SetHoveredActor(HoveredInteractedActor.Get(), InstanceHoveredMaterial);
		PlayerController->SetMouseCursorType(GetCursorTypeForActor(Actor));
	}
}

void UInteractionComponent::SetInteractActor(AActor* Actor)
{
	ClearInteractActor();

	check(Actor);
	TargetInteractedActor = Actor;

	SetUseOutlineActor(TargetInteractedActor.Get(), true);
	IInteractionInterface* InteractedInterface = Cast<IInteractionInterface>(TargetInteractedActor.Get());
	EInteractionRelation Relation = InteractedInterface->GetInteractionRelation();
	if (bForceAttack && InteractedInterface->CanEvenAttack())
	{
		Relation = EInteractionRelation::Hostile;
	}
	uint8 ColorIndex = (uint8)Relation;
	UKismetMaterialLibrary::SetVectorParameterValue(GetWorld(), OutlineParameters, TEXT("Color"), SelectionOverlayColors[ColorIndex]);
}

void UInteractionComponent::ClearInteractActor()
{
	if (TargetInteractedActor.Get())
	{
		SetUseOutlineActor(TargetInteractedActor.Get(), false);
	}

	TargetInteractedActor = nullptr;
}

void UInteractionComponent::Select(const FInputActionValue& Value)
{
	bOngoingSelection = Value.Get<bool>();
	if (HoveredInteractedActor.Get())
	{
		SetInteractActor(HoveredInteractedActor.Get());

		//TODO: Add to selection to HUD
		//1) Keep assist target move close to target
		//2) If close enough base at hostility try to attack or interact
		//3) After interact reset target

	}
	else
	{
		ClearInteractActor();
	}
}

void UInteractionComponent::ConfirmSelection(const FInputActionValue& Value)
{
	if (bOngoingSelection)
	{
		
		//InstanceMaterial->SetVectorParameterValue(TEXT("Color"), HostileTargetColor);

		//TargetActor = SelectedActor;
	}
	//TODO: Add assist target and go same behaviour as Select
}

AReignPlayerController* UInteractionComponent::GetPlayerController() const
{
	return PlayerController;
}

EReignMouseCursor UInteractionComponent::GetCursorTypeForActor(AActor* Actor) const
{
	if (auto Interactable = Cast<IInteractionInterface>(Actor))
	{
		const EInteractionRelation Relation = Interactable->GetInteractionRelation();
		const EInteractionType InteractionType = Interactable->GetInteractionType();

		switch (InteractionType)
		{
		case EInteractionType::PickUp:
			return EReignMouseCursor::ItemPickup;

		case EInteractionType::Character:
			if (bForceAttack)
			{
				return EReignMouseCursor::UnfriendlyAttack;
			}

			if (Relation == EInteractionRelation::Hostile)
			{
				return Interactable->CanInteract() ? EReignMouseCursor::Attack : EReignMouseCursor::Dead;
			}
			else if (Relation == EInteractionRelation::Neutral)
			{
				if (Interactable->CanInteract())
				{
					return EReignMouseCursor::Talk;
				}
			}
			break;
		}
	}

	return EReignMouseCursor::Default;
}

