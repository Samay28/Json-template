#include "MyBox.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
AMyBox::AMyBox()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	RootComponent = BoxMesh;
}

// Called when the game starts or when spawned
void AMyBox::BeginPlay()
{
	Super::BeginPlay();
}

void AMyBox::Initialize(FString ColorHex, int32 InitialHealth, int32 ScoreValue)
{
	Health = InitialHealth;
	Score = ScoreValue;

	if (!MaterialInstance)
	{
		MaterialInstance = UMaterialInstanceDynamic::Create(BoxMesh->GetMaterial(0), this);
		BoxMesh->SetMaterial(0, MaterialInstance);
	}

	FColor SRGBColor = FColor::FromHex(ColorHex);
	FLinearColor LinearColor = FLinearColor(SRGBColor);

	// Set the color parameter for the material
	MaterialInstance->SetVectorParameterValue(TEXT("BaseColor"), LinearColor);
}

// Called every frame
void AMyBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyBox::TakeDamageFromPlayer()
{
	Health--;
	if (Health <= 0)
	{
		Destroy();
	}
}
