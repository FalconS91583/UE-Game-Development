#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AdaptiveEnemyAIComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class YOURGAME_API UAdaptiveEnemyAIComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    void OnPlayerKilledMe(AActor* Player);
    void UpdateBehavior(AActor* Player);

protected:
    virtual void BeginPlay() override;

private:
    bool IsPlayerBehindWall(AActor* Player) const;

private:
    UPROPERTY()
    class UEnemyLearningComponent* LearningComponent;
};