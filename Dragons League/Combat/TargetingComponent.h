#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class YOURGAME_API UTargetingComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    AActor* FindClosestEnemy(float Radius);

protected:
    virtual void BeginPlay() override;
};