// Fill out your copyright notice in the Description page of Project Settings.


#include "TrovoScruberClientGameInstance.h"
#include "WebManager.h"

UTrovoScruberClientGameInstance* SingletonInstance;

void UTrovoScruberClientGameInstance::Init()
{
    // Singleton
	SingletonInstance = this;

    WebManager = NewObject<UWebManager>(this);
}

UWebManager* UTrovoScruberClientGameInstance::GetWebManager()
{
    return SingletonInstance ? SingletonInstance->WebManager : nullptr;
}
