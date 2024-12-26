#include "GameManager.h"
#include "Engine/World.h"
#include "MyBox.h"
#include "Materials/MaterialInstanceDynamic.h"
// Sets default values
AGameManager::AGameManager()
{
    PrimaryActorTick.bCanEverTick = false; // No need for ticking
    JSONURL = TEXT("https://raw.githubusercontent.com/CyrusCHAU/Varadise-Technical-Test/refs/heads/main/data.json");
}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
    Super::BeginPlay();

    // Start fetching JSON data
    FetchJSONData();
}

// Fetch JSON data from the online source
void AGameManager::FetchJSONData()
{
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
    Request->OnProcessRequestComplete().BindUObject(this, &AGameManager::ParseJSONData);

    Request->SetURL(JSONURL);
    Request->SetVerb(TEXT("GET"));
    Request->ProcessRequest();
}

// Parse JSON data
void AGameManager::ParseJSONData(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (!bWasSuccessful || !Response.IsValid() || !EHttpResponseCodes::IsOk(Response->GetResponseCode()))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to fetch JSON data. HTTP Error: %d"), Response.IsValid() ? Response->GetResponseCode() : -1);
        return;
    }

    FString ResponseContent = Response->GetContentAsString();
    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseContent);

    if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
    {
        const TArray<TSharedPtr<FJsonValue>>* Boxes;
        if (JsonObject->TryGetArrayField(TEXT("boxes"), Boxes))
        {
            for (const TSharedPtr<FJsonValue>& BoxValue : *Boxes)
            {
                TSharedPtr<FJsonObject> BoxObject = BoxValue->AsObject();
                if (BoxObject.IsValid())
                {
                    FString Type = BoxObject->GetStringField(TEXT("type"));
                    FString Color = BoxObject->GetStringField(TEXT("color"));
                    int32 Health = BoxObject->GetIntegerField(TEXT("health"));
                    int32 Score = BoxObject->GetIntegerField(TEXT("score"));

                    SpawnBox(Type, Color, Health, Score);
                }
            }
			UE_LOG(LogTemp, Error, TEXT("FoundBox"));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Invalid JSON structure: Missing 'boxes' array"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON content"));
    }
}

void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGameManager::SpawnBox(const FString& Type, const FString& Color, int32 Health, int32 Score)
{
    if (!GetWorld()) return;

    FActorSpawnParameters SpawnParams;
    FVector Location = FVector(FMath::RandRange(-500, 500), FMath::RandRange(-500, 500), 100);
    FRotator Rotation = FRotator::ZeroRotator;

    AMyBox* BoxActor = GetWorld()->SpawnActor<AMyBox>(AMyBox::StaticClass(), Location, Rotation, SpawnParams);
    if (BoxActor)
    {
        BoxActor->Initialize(Color, Health, Score);
        UE_LOG(LogTemp, Log, TEXT("Spawned Box - Type: %s, Color: %s, Health: %d, Score: %d"), *Type, *Color, Health, Score);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to spawn box actor"));
    }
}

