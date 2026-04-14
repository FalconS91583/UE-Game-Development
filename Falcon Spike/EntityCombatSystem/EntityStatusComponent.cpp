#include "EntityStatusComponent.h"
#include "EntityStatsComponent.h"
#include "EntityHealthComponent.h"
#include "TimerManager.h"

void UEntityStatusComponent::BeginPlay()
{
    Super::BeginPlay();

    Stats = GetOwner()->FindComponentByClass<UEntityStatsComponent>();
    Health = GetOwner()->FindComponentByClass<UEntityHealthComponent>();
}

void UEntityStatusComponent::ApplyBurn(float Duration, float Damage, float MagicPen)
{
    if (!Health || !Stats) return;

    float Resistance = Stats->GetElementalResistance(EElementType::Fire, MagicPen);
    float FinalDamage = Damage * (1 - Resistance);

    CurrentEffect = EElementType::Fire;

    float TickInterval = 0.5f;
    float TotalTicks = Duration / TickInterval;
    float DamagePerTick = FinalDamage / TotalTicks;

    GetWorld()->GetTimerManager().ClearTimer(DoTTimer);

    GetWorld()->GetTimerManager().SetTimer(DoTTimer, [this, DamagePerTick]()
    {
        if (Health)
            Health->ApplyDamage(DamagePerTick);

    }, TickInterval, true);

    GetWorld()->GetTimerManager().SetTimer(EffectTimer, [this]()
    {
        GetWorld()->GetTimerManager().ClearTimer(DoTTimer);
        ResetEffect();

    }, Duration, false);
}

void UEntityStatusComponent::ApplyChilled(float Duration, float SlowMultiplier, float MagicPen)
{
    if (!Stats) return;

    float Resistance = Stats->GetElementalResistance(EElementType::Ice, MagicPen);
    float FinalDuration = Duration * (1 - Resistance);

    CurrentEffect = EElementType::Ice;

    // TODO: Apply slow to movement component

    GetWorld()->GetTimerManager().SetTimer(EffectTimer, this, &UEntityStatusComponent::ResetEffect, FinalDuration, false);
}

void UEntityStatusComponent::ApplyElectrify(float Duration, float Damage, float Charge, float MagicPen)
{
    if (!Stats || !Health) return;

    float Resistance = Stats->GetElementalResistance(EElementType::Lightning, MagicPen);
    float FinalCharge = Charge * (1 - Resistance);

    CurrentCharge += FinalCharge;

    if (CurrentCharge >= MaxCharge)
    {
        Health->ApplyDamage(Damage);
        ResetEffect();
        return;
    }

    CurrentEffect = EElementType::Lightning;

    GetWorld()->GetTimerManager().SetTimer(EffectTimer, this, &UEntityStatusComponent::ResetEffect, Duration, false);
}

void UEntityStatusComponent::ApplyRadiation(float Duration, float Damage, float Charge, float MagicPen)
{
    if (!Stats || !Health) return;

    float Resistance = Stats->GetElementalResistance(EElementType::Radiation, MagicPen);
    float FinalCharge = Charge * (1 - Resistance);

    CurrentCharge += FinalCharge;
    CurrentEffect = EElementType::Radiation;

    float TickInterval = 0.5f;

    GetWorld()->GetTimerManager().ClearTimer(DoTTimer);

    GetWorld()->GetTimerManager().SetTimer(DoTTimer, [this, Damage, TickInterval]()
    {
        if (Health)
            Health->ApplyDamage(Damage * TickInterval);

    }, TickInterval, true);

    GetWorld()->GetTimerManager().SetTimer(EffectTimer, [this]()
    {
        GetWorld()->GetTimerManager().ClearTimer(DoTTimer);
        ResetEffect();

    }, Duration, false);
}

void UEntityStatusComponent::ApplyAcid(float Duration, float ArmorReduction, float Damage)
{
    if (!Stats || !Health) return;

    CurrentEffect = EElementType::Acid;

    Stats->ApplyArmorDebuff(ArmorReduction);
    Health->ApplyDamage(Damage);

    GetWorld()->GetTimerManager().SetTimer(EffectTimer, [this]()
    {
        if (Stats)
            Stats->ApplyArmorDebuff(0.f);

        ResetEffect();

    }, Duration, false);
}

void UEntityStatusComponent::ApplyMagnet(float Duration, float Charge, float Damage)
{
    if (!Health) return;

    CurrentCharge += Charge;

    if (CurrentCharge >= MaxCharge)
    {
        Health->ApplyDamage(Damage);

        CurrentEffect = EElementType::Magnetic;

        // TODO: Add pull logic (RadialForce / manual movement)

        GetWorld()->GetTimerManager().SetTimer(EffectTimer, this, &UEntityStatusComponent::ResetEffect, Duration, false);

        CurrentCharge = 0.f;
    }
}

void UEntityStatusComponent::ResetEffect()
{
    CurrentEffect = EElementType::None;
    CurrentCharge = 0.f;

    GetWorld()->GetTimerManager().ClearTimer(DoTTimer);
}

bool UEntityStatusComponent::CanBeApplied(EElementType Element) const
{
    if (Element == CurrentEffect)
        return true;

    return CurrentEffect == EElementType::None;
}