#include "EntityHealthComponent.h"
#include "EntityStatsComponent.h"
#include "Kismet/KismetMathLibrary.h"

UEntityHealthComponent::UEntityHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UEntityHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    Stats = GetOwner()->FindComponentByClass<UEntityStatsComponent>();

    if (Stats)
        CurrentHp = Stats->GetMaxHealth();

    if (bCanRegenerateHealth)
    {
        GetWorld()->GetTimerManager().SetTimer(
            RegenTimer,
            [this]()
            {
                Heal(Stats->GetHealthRegen());
            },
            RegenInterval,
            true
        );
    }
}

bool UEntityHealthComponent::TakeDamage(float Damage, float ElementalDamage, EElementType Element, AActor* Attacker)
{
    if (bIsDead)
        return false;

    if (AttackEvaded())
        return false;

    UEntityStatsComponent* AttackerStats = nullptr;

    if (Attacker)
        AttackerStats = Attacker->FindComponentByClass<UEntityStatsComponent>();

    float ArmorPen = AttackerStats ? AttackerStats->GetArmorPenetration() : 0.f;
    float ElementPen = AttackerStats ? AttackerStats->GetElementalPenetration() : 0.f;

    float Resistance = Stats->GetElementalResistance(Element, ElementPen);
    float ElementalDamageTaken = ElementalDamage * (1 - Resistance);

    float Mitigation = Stats->GetArmorMitigation(ArmorPen);
    float PhysicalDamageTaken = Damage * (1 - Mitigation);

    float TotalDamage = PhysicalDamageTaken + ElementalDamageTaken;

    ApplyDamage(TotalDamage);

    OnTakingDamage.Broadcast();

    return true;
}