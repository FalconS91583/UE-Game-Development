USTRUCT(BlueprintType)
struct FEnemyExperience
{
    GENERATED_BODY()

    UPROPERTY()
    FString SituationTag; // np. "PlayerBehindWall"

    UPROPERTY()
    FVector LastKnownPlayerLocation;

    UPROPERTY()
    float SuccessScore = 0.f; // jak dobrze zadziałało

    UPROPERTY()
    int32 TimesUsed = 0;
};