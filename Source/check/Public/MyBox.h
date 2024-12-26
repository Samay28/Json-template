// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyBox.generated.h"

UCLASS()
class CHECK_API AMyBox : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyBox();

	void Initialize(FString ColorHex, int32 InitialHealth, int32 ScoreValue);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void TakeDamageFromPlayer();

private:
	UStaticMeshComponent *BoxMesh;

	int32 Health;
	int32 Score;

	UMaterialInstanceDynamic *MaterialInstance;
};
