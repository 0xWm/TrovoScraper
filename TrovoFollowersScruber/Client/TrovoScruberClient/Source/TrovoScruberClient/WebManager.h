// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "WebManager.generated.h"


DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnReceiveFollowersListDelegate, bool, bWasSuccessful,  const TArray<FString>&, Followers);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TROVOSCRUBERCLIENT_API UWebManager : public UActorComponent
{
	GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable)
    void InitServerData(const FString& InServerURL, const FString& InPort, const FString& InBroadcasterName, int32 InFollowerCount);

    UFUNCTION(BlueprintCallable)
    void GetFollowersList(const FOnReceiveFollowersListDelegate& Callback);
    void OnGetFollowersList(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

    // Delegate
    UPROPERTY()
    FOnReceiveFollowersListDelegate OnReceiveFollowersListDelegate;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ServerInfo|Server")
    FString ServerURL;
	
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ServerInfo|Server")
    FString Port;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ServerInfo|Server")
	FString HeaderName = FString(TEXT("Content-Type"));

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ServerInfo|Server")
	FString HeaderValue = FString(TEXT("application/json"));
	
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ServerInfo|Broadcaster")
    FString BroadcasterName;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ServerInfo|Broadcaster")
	int32 FollowerCount;

};
