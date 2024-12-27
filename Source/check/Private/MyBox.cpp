#include "MyBox.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

AMyBox::AMyBox()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create a static mesh component for the box
    BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
    RootComponent = BoxMesh;

    // Set default values
    Health = 0;
    Score = 0;
    Color = FLinearColor::White;
}

void AMyBox::BeginPlay()
{
    Super::BeginPlay();
}

void AMyBox::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMyBox::InitializeBox(const FLinearColor& BoxColor, int32 BoxHealth, int32 BoxScore)
{
    // Set properties
    Color = BoxColor;
    Health = BoxHealth;
    Score = BoxScore;

    // Apply color to the box's material
    if (BoxMesh)
    {
        UMaterialInstanceDynamic* DynamicMaterial = BoxMesh->CreateAndSetMaterialInstanceDynamic(0);
        if (DynamicMaterial)
        {
            DynamicMaterial->SetVectorParameterValue(FName("BaseColor"), Color);
        }
    }

    UE_LOG(LogTemp, Log, TEXT("Box Initialized - Health: %d, Score: %d, Color: (%f, %f, %f)"), 
        Health, Score, Color.R, Color.G, Color.B);
}
