// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Http.h"
#include "GameManager.generated.h"

UCLASS()
class CHECK_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManager();

	void SpawnBox(const FString& Type, const FString& Color, int32 Health, int32 Score);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void FetchJSONData();
	void ParseJSONData(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	FString JSONURL;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
