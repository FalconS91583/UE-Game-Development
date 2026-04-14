#include "TargetingComponent.h"
#include "Kismet/GameplayStatics.h"

void UTargetingComponent::BeginPlay()
{
    Super::BeginPlay();
}

AActor* UTargetingComponent::FindClosestEnemy(float Radius)
{
    FVector Origin = GetOwner()->GetActorLocation();

    TArray<FOverlapResult> Hits;

    FCollisionShape Sphere = FCollisionShape::MakeSphere(Radius);

    bool bHit = GetWorld()->OverlapMultiByChannel(
        Hits,
        Origin,
        FQuat::Identity,
        ECC_Pawn,
        Sphere
    );

    AActor* Closest = nullptr;
    float MinDist = FLT_MAX;

    for (auto& Hit : Hits)
    {
        AActor* Actor = Hit.GetActor();

        if (Actor == GetOwner()) continue;

        float Dist = FVector::Dist(Origin, Actor->GetActorLocation());

        if (Dist < MinDist)
        {
            MinDist = Dist;
            Closest = Actor;
        }
    }

    return Closest;
}