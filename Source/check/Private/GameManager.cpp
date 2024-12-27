#include "GameManager.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

AGameManager::AGameManager()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AGameManager::BeginPlay()
{
    Super::BeginPlay();
    FetchJSON();
}

void AGameManager::FetchJSON()
{
    // Create an HTTP request
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
    Request->OnProcessRequestComplete().BindUObject(this, &AGameManager::OnResponseReceived);
    Request->SetURL("https://raw.githubusercontent.com/CyrusCHAU/Varadise-Technical-Test/refs/heads/main/data.json");
    Request->SetVerb("GET");
    Request->ProcessRequest();
}

void AGameManager::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (!bWasSuccessful || !Response.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to fetch JSON data!"));
        return;
    }

    FBoxData BoxData;
    if (FJsonObjectConverter::JsonObjectStringToUStruct<FBoxData>(Response->GetContentAsString(), &BoxData, 0, 0))
    {
        UE_LOG(LogTemp, Log, TEXT("Successfully parsed JSON data!"));

        // Iterate through objects and spawn them
        for (const FBoxObject& Object : BoxData.Objects)
        {
            const FBoxType* FoundType = BoxData.Types.FindByPredicate([&](const FBoxType& Type)
            {   
                UE_LOG(LogTemp, Warning, TEXT("Not Spawned Box"));
                return Type.Name == Object.Type;
            });

            if (FoundType)
            {
                SpawnBox(Object, *FoundType);
                UE_LOG(LogTemp, Warning, TEXT("Spawned Box"));
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to parse JSON data!"));
    }
}

void AGameManager::SpawnBox(const FBoxObject& BoxObject, const FBoxType& BoxType)
{
    if (!BoxActorClass) // Ensure the class is set
    {
        UE_LOG(LogTemp, Warning, TEXT("BoxActorClass is not set!"));
        return;
    }

    // Create transform
    FTransform Transform;
    Transform.SetLocation(BoxObject.Transform.Location);
    Transform.SetRotation(FQuat(BoxObject.Transform.Rotation));
    Transform.SetScale3D(BoxObject.Transform.Scale);

    // Spawn the box
    AActor* Box = GetWorld()->SpawnActor<AActor>(BoxActorClass, Transform);
    if (Box)
    {
        // Access the StaticMeshComponent of the spawned actor
        UStaticMeshComponent* StaticMeshComponent = Box->FindComponentByClass<UStaticMeshComponent>();
        if (StaticMeshComponent)
        {
            // Set dynamic material and apply color
            UMaterialInstanceDynamic* DynamicMaterial = StaticMeshComponent->CreateAndSetMaterialInstanceDynamic(0);
            if (DynamicMaterial && BoxType.Color.Num() == 3)
            {
                FLinearColor BoxColor(BoxType.Color[0] / 255.0f, BoxType.Color[1] / 255.0f, BoxType.Color[2] / 255.0f, 1.0f);
                DynamicMaterial->SetVectorParameterValue(FName("BaseColor"), BoxColor);
            }

            // Apply other properties as needed (e.g., Health, Score)
            UE_LOG(LogTemp, Log, TEXT("Box Spawned - Type: %s, Health: %d, Score: %d"), 
                *BoxType.Name, BoxType.Health, BoxType.Score);
        }
    }
}
