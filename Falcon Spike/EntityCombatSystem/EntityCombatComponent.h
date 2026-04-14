#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EntityCombatComponent.generated.h"

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
class YOURGAME_API UEntityCombatComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UEntityCombatComponent();

    bool PerformAttackOnTarget(AActor* Target);
    bool PerformRangedAttack(AActor* Target, float DamageMultiplier, bool bForceCrit);

private:
    virtual void BeginPlay() override;

    void ApplyStatusEffect(AActor* Target, EElementType Element, float ScaleFactor = 1.0f);

private:
    UPROPERTY()
    class UEntityStatsComponent* Stats;

    // Config
    UPROPERTY(EditDefaultsOnly)
    float DefaultDuration = 3.f;

    UPROPERTY(EditDefaultsOnly)
    float ChillSlowMultiplier = 0.2f;

    UPROPERTY(EditDefaultsOnly)
    float ElectrifyChargeBuildUp = 0.4f;

    UPROPERTY(EditDefaultsOnly)
    float FireScale = 1.f;

    UPROPERTY(EditDefaultsOnly)
    float LightningScale = 2.f;

    UPROPERTY(EditDefaultsOnly)
    float RadiationScale = 0.2f;

    UPROPERTY(EditDefaultsOnly)
    float AcidScale = 1.f;

    UPROPERTY(EditDefaultsOnly)
    float MagneticScale = 0.3f;
};