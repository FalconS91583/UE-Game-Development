#include "HeroEvolutionComponent.h"
#include "HeroAbilityComponent.h"

void UHeroEvolutionComponent::BeginPlay()
{
    Super::BeginPlay();

    AbilityComponent = GetOwner()->FindComponentByClass<UHeroAbilityComponent>();
}

void UHeroEvolutionComponent::AddExperience(float Amount)
{
    CurrentXP += Amount;

    CheckEvolution();
}

void UHeroEvolutionComponent::CheckEvolution()
{
    if (!bIsDragonForm && CurrentXP >= RequiredXP)
    {
        TransformToDragon();
    }
}

void UHeroEvolutionComponent::TransformToDragon()
{
    bIsDragonForm = true;

    if (AbilityComponent)
    {
        AbilityComponent->SwitchForm(EHeroForm::Dragon);
    }

    UE_LOG(LogTemp, Warning, TEXT("Hero evolved into DRAGON FORM"));
}