// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TrovoScruberClientGameInstance.generated.h"

class UWebManager;

/**
 * 
 */
UCLASS()
class TROVOSCRUBERCLIENT_API UTrovoScruberClientGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	virtual void Init() override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static UWebManager* GetWebManager();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UWebManager* WebManager;	
};
