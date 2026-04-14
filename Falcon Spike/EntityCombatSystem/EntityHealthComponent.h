#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EntityHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamageTaken, float, Damage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTakingDamage);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class YOURGAME_API UEntityHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UEntityHealthComponent();

    bool TakeDamage(float Damage, float ElementalDamage, EElementType Element, AActor* Attacker);

    void ApplyDamage(float Damage);
    void Heal(float Amount);

    float GetHealthPercent() const;

    bool IsDead() const { return bIsDead; }

    UPROPERTY(BlueprintAssignable)
    FOnDeath OnDeath;

    UPROPERTY(BlueprintAssignable)
    FOnDamageTaken OnDamageTaken;

    UPROPERTY(BlueprintAssignable)
    FOnTakingDamage OnTakingDamage;

protected:
    virtual void BeginPlay() override;

private:
    void Die();
    bool AttackEvaded();

private:

    UPROPERTY()
    class UEntityStatsComponent* Stats;

    UPROPERTY(EditAnywhere)
    float CurrentHp = 0.f;

    UPROPERTY(EditAnywhere)
    bool bIsDead = false;

    UPROPERTY(EditAnywhere)
    bool bCanRegenerateHealth = false;

    UPROPERTY(EditAnywhere)
    float RegenInterval = 1.f;

    FTimerHandle RegenTimer;
};