#include "ReignPlayerController.h"

#include "ReignOfConquest/Systems/Interaction/InteractionComponent.h"

AReignPlayerController::AReignPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Interaction = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));
}

void AReignPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	Interaction->SetupInputComponent(InputComponent);
}

void AReignPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(!CursorWidgetClass.IsNull())
	UClass* WidgetClass = CursorWidgetClass.LoadSynchronous();
	check(WidgetClass)
	CursorWidgetInstance = CreateWidget<UReignCursorWidget>(this, WidgetClass);
	check(CursorWidgetInstance)
	SetMouseCursorWidget(EMouseCursor::Default, CursorWidgetInstance);
}

void AReignPlayerController::SetMouseCursorType(EReignMouseCursor Type) const
{
	CursorWidgetInstance->SetCursorType(Type);
}
