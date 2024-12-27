#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Http.h"
#include "JsonObjectConverter.h"
#include "GameManager.generated.h"
USTRUCT()
struct FTransformData
{
    GENERATED_BODY()

    FVector Location;
    FRotator Rotation;
    FVector Scale;
};

USTRUCT()
struct FBoxType
{
    GENERATED_BODY()

    FString Name;
    TArray<float> Color; // [R, G, B]
    int32 Health;
    int32 Score;
};

USTRUCT()
struct FBoxObject
{
    GENERATED_BODY()

    FString Type;
    FTransformData Transform;
};

USTRUCT()
struct FBoxData
{
    GENERATED_BODY()

    TArray<FBoxType> Types;
    TArray<FBoxObject> Objects;
};

UCLASS()
class CHECK_API AGameManager : public AActor
{
    GENERATED_BODY()

public:
    AGameManager();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category = "Spawning")
    TSubclassOf<AActor> BoxActorClass;

    void FetchJSON();
    void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
    void SpawnBox(const FBoxObject& BoxObject, const FBoxType& BoxType);
};