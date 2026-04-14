#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HeroAbilityComponent.generated.h"

UENUM(BlueprintType)
enum class EHeroForm : uint8
{
    Human,
    Dragon
};

USTRUCT(BlueprintType)
struct FAbilityData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    FName AbilityName;

    UPROPERTY(EditAnywhere)
    float Cooldown = 1.f;

    UPROPERTY(EditAnywhere)
    float Damage = 10.f;

    float LastUsedTime = -100.f;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class YOURGAME_API UHeroAbilityComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    void UseAbility(int32 Index);
    void SwitchForm(EHeroForm NewForm);

protected:
    virtual void BeginPlay() override;

private:
    bool CanUseAbility(const FAbilityData& Ability) const;

private:
    UPROPERTY(EditAnywhere)
    TArray<FAbilityData> HumanAbilities;

    UPROPERTY(EditAnywhere)
    TArray<FAbilityData> DragonAbilities;

    EHeroForm CurrentForm = EHeroForm::Human;
};