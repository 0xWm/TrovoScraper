// Fill out your copyright notice in the Description page of Project Settings.

#include "WebManager.h"
#include "Runtime/Online/HTTP/Public/Http.h"

#pragma clang optimize off

void UWebManager::InitServerData(const FString& InServerURL, const FString& InPort, const FString& InBroadcasterName, int32 InFollowerCount)
{
	ServerURL = InServerURL;
	Port = InPort;
	BroadcasterName = InBroadcasterName;
	FollowerCount = InFollowerCount;
}

void UWebManager::GetFollowersList(const FOnReceiveFollowersListDelegate& Callback)
{
    FHttpModule* Http = &FHttpModule::Get();
	if (!Http)
	{
        Callback.ExecuteIfBound(false, TArray<FString>());

		return;
    }

    FString FullURL = ServerURL + ":" + Port + "/GetFollowers";
	UE_LOG(LogTemp, Warning, TEXT("Full URL is: %s"), *FullURL)

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UWebManager::OnGetFollowersList);
	Request->SetURL(FullURL);
	Request->SetVerb("POST");

	// Headers
	Request->SetHeader(HeaderName, HeaderValue);

	// Content
	FString JsonStr;
	TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> JsonWriter = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&JsonStr);
	JsonWriter->WriteObjectStart();
	JsonWriter->WriteObjectStart("params");
	JsonWriter->WriteValue("broadcaster_name", *BroadcasterName);
	JsonWriter->WriteValue("follower_count", FollowerCount);
	JsonWriter->WriteObjectEnd();
	JsonWriter->WriteObjectEnd();
	JsonWriter->Close();
	UE_LOG(LogTemp, Warning, TEXT("Full content is: %s"), *JsonStr)
	Request->SetContentAsString(JsonStr);

	OnReceiveFollowersListDelegate = Callback;
	Request->ProcessRequest();
}

void UWebManager::OnGetFollowersList(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!bWasSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT(" Request Was not successful"));
		OnReceiveFollowersListDelegate.ExecuteIfBound(false, TArray<FString>());

		return;
	}

	FString Body = Response->GetContentAsString();
	UE_LOG(LogTemp, Warning, TEXT("Data recieved: %s"), *Body);
	
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Body);

	// Check Response validity
	if (!Response.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Response Not Valid"));
		OnReceiveFollowersListDelegate.ExecuteIfBound(false, TArray<FString>());

		return;
	}

	// Deserialize received Json
	if (!FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to deserialize Json"));
		OnReceiveFollowersListDelegate.ExecuteIfBound(false, TArray<FString>());

		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Json deserialized"));


	const TSharedPtr<FJsonObject>* DataObject;
	JsonObject->TryGetObjectField("data", DataObject);
	if (!DataObject)
	{
		UE_LOG(LogTemp, Warning, TEXT("DataObject nullptr"));
		OnReceiveFollowersListDelegate.ExecuteIfBound(false, TArray<FString>());

		return;
	}
	
	TArray<FString> NickNames;
	const TArray<TSharedPtr<FJsonValue>>* NickNamesObject = nullptr;
	if ((*DataObject)->TryGetArrayField(TEXT("nickNames"), NickNamesObject))
	{
		for (int32 i = 0; i < NickNamesObject->Num(); i++)
		{
			TSharedPtr<FJsonObject> Object = (*NickNamesObject)[i]->AsObject();
			if (Object.IsValid())
			{
				FString NickName;
				if (Object->TryGetStringField(TEXT("nickName"), NickName))
				{
					NickNames.Add(NickName);
				}
			}
		}
	}

	OnReceiveFollowersListDelegate.ExecuteIfBound(bWasSuccessful, NickNames);
}