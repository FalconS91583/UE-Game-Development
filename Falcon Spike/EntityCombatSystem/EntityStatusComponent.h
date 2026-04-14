#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EntityStatusComponent.generated.h"

UENUM(BlueprintType)
enum class EElementType : uint8
{
    None,
    Fire,
    Ice,
    Lightning,
    Radiation,
    Acid,
    Magnetic
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class YOURGAME_API UEntityStatusComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    void ApplyBurn(float Duration, float Damage, float MagicPen = 0.f);
    void ApplyChilled(float Duration, float SlowMultiplier, float MagicPen = 0.f);
    void ApplyElectrify(float Duration, float Damage, float Charge, float MagicPen = 0.f);
    void ApplyRadiation(float Duration, float Damage, float Charge, float MagicPen = 0.f);
    void ApplyAcid(float Duration, float ArmorReduction, float Damage);
    void ApplyMagnet(float Duration, float Charge, float Damage);

    bool CanBeApplied(EElementType Element) const;

protected:
    virtual void BeginPlay() override;

private:
    void ResetEffect();

private:
    UPROPERTY()
    class UEntityStatsComponent* Stats;

    UPROPERTY()
    class UEntityHealthComponent* Health;

    EElementType CurrentEffect = EElementType::None;

    float CurrentCharge = 0.f;
    float MaxCharge = 1.f;

    // Timery
    FTimerHandle EffectTimer;
    FTimerHandle DoTTimer;
};