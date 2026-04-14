#include "EntityCombatComponent.h"
#include "EntityStatsComponent.h"
#include "DamageableInterface.h"
#include "EntityStatusComponent.h"

UEntityCombatComponent::UEntityCombatComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UEntityCombatComponent::BeginPlay()
{
    Super::BeginPlay();

    Stats = GetOwner()->FindComponentByClass<UEntityStatsComponent>();
}

bool UEntityCombatComponent::PerformAttackOnTarget(AActor* Target)
{
    if (!Target || !Target->Implements<UDamageableInterface>())
        return false;

    bool bIsCrit = false;
    float Damage = Stats->GetPhysicalDamage(bIsCrit);

    EElementType Element;
    float ElementalDamage = Stats->GetElementalDamage(Element, 0.6f);

    IDamageableInterface::Execute_TakeDamage(Target, Damage, ElementalDamage, Element, GetOwner());

    if (Element != EElementType::None)
        ApplyStatusEffect(Target, Element);

    return true;
}

bool UEntityCombatComponent::PerformRangedAttack(AActor* Target, float DamageMultiplier, bool bForceCrit)
{
    if (!Target || !Target->Implements<UDamageableInterface>())
        return false;

    bool bIsCrit = false;
    float Damage = Stats->GetPhysicalDamage(bIsCrit);

    if (bForceCrit)
        bIsCrit = true;

    Damage *= DamageMultiplier;

    EElementType Element;
    float ElementalDamage = Stats->GetElementalDamage(Element, 0.6f);

    IDamageableInterface::Execute_TakeDamage(Target, Damage, ElementalDamage, Element, GetOwner());

    if (Element != EElementType::None)
        ApplyStatusEffect(Target, Element);

    UE_LOG(LogTemp, Warning, TEXT("Damage: %f"), Damage);

    return true;
}