#include "AdaptiveEnemyAIComponent.h"
#include "EnemyLearningComponent.h"
#include "Kismet/KismetSystemLibrary.h"

void UAdaptiveEnemyAIComponent::BeginPlay()
{
    Super::BeginPlay();

    LearningComponent = GetOwner()->FindComponentByClass<UEnemyLearningComponent>();
}

bool UAdaptiveEnemyAIComponent::IsPlayerBehindWall(AActor* Player) const
{
    FHitResult Hit;

    FVector Start = GetOwner()->GetActorLocation();
    FVector End = Player->GetActorLocation();

    return GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility);
}

void UAdaptiveEnemyAIComponent::OnPlayerKilledMe(AActor* Player)
{
    if (!LearningComponent || !Player) return;

    if (IsPlayerBehindWall(Player))
    {
        LearningComponent->RecordExperience(
            "PlayerBehindWall",
            Player->GetActorLocation(),
            false
        );
    }
}

void UAdaptiveEnemyAIComponent::UpdateBehavior(AActor* Player)
{
    if (!LearningComponent || !Player) return;

    if (IsPlayerBehindWall(Player))
    {
        FVector LearnedPosition = LearningComponent->GetBestResponseLocation("PlayerBehindWall");

        if (!LearnedPosition.IsZero())
        {
            // AI próbuje flankować / obejść
            UE_LOG(LogTemp, Warning, TEXT("Using learned behavior: flanking player"));

            // TODO: Move AI to LearnedPosition
        }
    }
}