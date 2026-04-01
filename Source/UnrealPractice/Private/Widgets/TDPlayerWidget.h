// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDPlayerWidget.generated.h"

class UTDPlayerWidgetViewModel;

UCLASS()
class UTDPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetViewModel(UTDPlayerWidgetViewModel* InViewModel);
	
private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UTDPlayerWidgetViewModel> ViewModel;
};
