#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HeroEvolutionComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class YOURGAME_API UHeroEvolutionComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    void AddExperience(float Amount);

protected:
    virtual void BeginPlay() override;

private:
    void CheckEvolution();
    void TransformToDragon();

private:
    UPROPERTY(EditAnywhere)
    float CurrentXP = 0.f;

    UPROPERTY(EditAnywhere)
    float RequiredXP = 100.f;

    UPROPERTY(EditAnywhere)
    bool bIsDragonForm = false;

    UPROPERTY()
    class UHeroAbilityComponent* AbilityComponent;
};