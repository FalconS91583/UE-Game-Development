#include "EnemyLearningComponent.h"

void UEnemyLearningComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UEnemyLearningComponent::RecordExperience(FString Situation, FVector PlayerLocation, bool bSuccess)
{
    for (FEnemyExperience& Exp : Memory)
    {
        if (Exp.SituationTag == Situation)
        {
            Exp.TimesUsed++;

            if (bSuccess)
                Exp.SuccessScore += 1.f;
            else
                Exp.SuccessScore -= 0.5f;

            Exp.LastKnownPlayerLocation = PlayerLocation;
            return;
        }
    }

    FEnemyExperience NewExp;
    NewExp.SituationTag = Situation;
    NewExp.LastKnownPlayerLocation = PlayerLocation;
    NewExp.SuccessScore = bSuccess ? 1.f : 0.f;
    NewExp.TimesUsed = 1;

    Memory.Add(NewExp);
}

FEnemyExperience* UEnemyLearningComponent::FindBestExperience(FString Situation)
{
    FEnemyExperience* Best = nullptr;
    float BestScore = -9999.f;

    for (FEnemyExperience& Exp : Memory)
    {
        if (Exp.SituationTag == Situation)
        {
            float Score = Exp.SuccessScore / Exp.TimesUsed;

            if (Score > BestScore)
            {
                BestScore = Score;
                Best = &Exp;
            }
        }
    }

    return Best;
}

FVector UEnemyLearningComponent::GetBestResponseLocation(FString Situation)
{
    FEnemyExperience* Exp = FindBestExperience(Situation);

    if (Exp)
    {
        return Exp->LastKnownPlayerLocation;
    }

    return FVector::ZeroVector;
}