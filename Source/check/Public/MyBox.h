#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyBox.generated.h"

UCLASS()
class CHECK_API AMyBox : public AActor
{
    GENERATED_BODY()
    
public:
    AMyBox();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // Set up the box's properties
    void InitializeBox(const FLinearColor& BoxColor, int32 BoxHealth, int32 BoxScore);

private:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* BoxMesh;

    UPROPERTY(EditAnywhere, Category = "Box Properties")
    int32 Health;

    UPROPERTY(EditAnywhere, Category = "Box Properties")
    int32 Score;

    UPROPERTY(EditAnywhere, Category = "Box Properties")
    FLinearColor Color;
};
