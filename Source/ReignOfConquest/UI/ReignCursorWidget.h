// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "ReignTypes.h"
#include "ReignCursorWidget.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class UReignCursorWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintImplementableEvent)
	void SetCursorType(EReignMouseCursor Type);

	UPROPERTY(BlueprintReadOnly)
	EReignMouseCursor CurrentType = EReignMouseCursor::Default;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UImage> CursorImage;
};
