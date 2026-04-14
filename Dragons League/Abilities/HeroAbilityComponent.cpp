#include "HeroAbilityComponent.h"
#include "Kismet/GameplayStatics.h"

void UHeroAbilityComponent::BeginPlay()
{
    Super::BeginPlay();
}

bool UHeroAbilityComponent::CanUseAbility(const FAbilityData& Ability) const
{
    float Time = GetWorld()->GetTimeSeconds();
    return Time >= Ability.LastUsedTime + Ability.Cooldown;
}

void UHeroAbilityComponent::UseAbility(int32 Index)
{
    TArray<FAbilityData>& Abilities = 
        (CurrentForm == EHeroForm::Human) ? HumanAbilities : DragonAbilities;

    if (!Abilities.IsValidIndex(Index)) return;

    FAbilityData& Ability = Abilities[Index];

    if (!CanUseAbility(Ability)) return;

    Ability.LastUsedTime = GetWorld()->GetTimeSeconds();

    UE_LOG(LogTemp, Warning, TEXT("Used Ability: %s | Damage: %f"),
        *Ability.AbilityName.ToString(),
        Ability.Damage);

    // TODO: spawn projectile / apply damage
}

void UHeroAbilityComponent::SwitchForm(EHeroForm NewForm)
{
    CurrentForm = NewForm;

    UE_LOG(LogTemp, Warning, TEXT("Switched form to: %s"),
        (NewForm == EHeroForm::Dragon ? TEXT("Dragon") : TEXT("Human")));
}