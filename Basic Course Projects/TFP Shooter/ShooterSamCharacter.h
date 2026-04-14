
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"

#include "Gun.h"

#include "ShooterSamCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);


UCLASS(abstract)
class AShooterSamCharacter : public ACharacter
{
	GENERATED_BODY()

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
protected:

	
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;


	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;


	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseLookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* ShootAction;

public:

	
	AShooterSamCharacter();	

protected:
	virtual void BeginPlay() override;


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	
	void Move(const FInputActionValue& Value);


	void Look(const FInputActionValue& Value);

public:


	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);


	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();

public:


	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	void Shoot();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AGun> GunClass;
	
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.0f;

	float Health;

	UPROPERTY(BlueprintReadOnly)
	bool IsAlive = true;

	AGun* Gun;

	void UpdateHUD();

	UFUNCTION()
	void OnDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};

