#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyLearningComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class YOURGAME_API UEnemyLearningComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    void RecordExperience(FString Situation, FVector PlayerLocation, bool bSuccess);
    FVector GetBestResponseLocation(FString Situation);

protected:
    virtual void BeginPlay() override;

private:
    FEnemyExperience* FindBestExperience(FString Situation);

private:
    UPROPERTY()
    TArray<FEnemyExperience> Memory;
};