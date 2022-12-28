// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"



UENUM(BlueprintType)
enum class EMovementStatus : uint8
{
	EMS_Normal    UMETA(DisplayName = "Normal"),
	EMS_Sprinting  UMETA(DisplayName = "Sprinting"),
	EMS_Dead       UMETA(DisplayName = "Dead"),
	EMS_Max        UMETA(DisplayName = "DefaultMAX")
};

UENUM(BlueprintType)
enum class EStaminaStatus :uint8
{
	ESS_Normal                       UMETA(DisplayName = "Normal"),
	ESS_BelowMinimum             UMETA(DisplayName = "BelowMinimum"),
	ESS_Exhausted                    UMETA(DisplayName = "Exhausted"),
	ESS_ExhaustedRecovering      UMETA(DisplayName = "ExhaustedRecovering"),

	ESS_Max UMETA(DisplayName = "DefaultMAX")
};

UCLASS()
class SUNTEMPLE_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	UPROPERTY(EditDefaultsOnly, Category = "SaveDate")
	TSubclassOf<class AItemStorage> WeaponStorage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool bHasCombatTarget;

	FORCEINLINE void SetHasCombatTarget(bool HasTarget) { bHasCombatTarget = HasTarget; }

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
	FVector CombatTargetLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller")
	class AMainPlayerController* MainPlayerController;

	TArray<FVector> PickupLocations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	class UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	class USoundCue* HitSound;

	

	UFUNCTION(BlueprintCallable)
	void ShowPickupLocation();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
	EMovementStatus MovementStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
	EStaminaStatus StaminaStatus;
	
	FORCEINLINE void SetStaminaStatus(EStaminaStatus Status) { StaminaStatus = Status; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StaminaDrainRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MinSprintStamina;

	float InterpSpeed;
	bool bInterpToEnemy;
	void SetInterpToEnemy(bool Interp);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	class AEnemy* CombatTarget;

	FORCEINLINE void SetCombatTarget(AEnemy* Target) { CombatTarget = Target; }

	FRotator GetLookAtRotationYaw(FVector Target);

	// ĳ������ �̵� ���� �� �޸��� �ӵ�
	void SetMovementStatus(EMovementStatus Status);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Running")
	float RunningSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Running")
	float SprintSpeed;

	bool bShiftKeyDown;


	// ����Ʈ�� ������ ������ ��������
	void ShiftKeyDown();

	// ����Ʈ�� ���� �������� ����
	void ShiftKeyUp();

	// ī�޶� ���� �� ī�޶� ��ġ ���� ĳ���� �ڰ� �⺻
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	// ī�޶� ȸ�� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	/**
	/*
	/* �÷��̾� ����
	/*
	*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly , Category = "Player Stats")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
	float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	int32 Coins;

	void DecreamentHealth(float Amount);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController* EventInstigator, AActor * DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	void IncreamentCoins(int32 Amount);

	UFUNCTION(BlueprintCallable)
	void IncreamentHealth(float Amount);

	void Die();

	virtual void Jump() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//�� �� �̵� �Լ�
	void MoveForward(float Value);

	//�� �̵� �Լ�
	void MoveRight(float Value);

	void Turn(float Value);

	void LookUp(float Value);

	bool bMovingForward;
	bool bMovingRight;

	bool CanMove(float Value);


	//ȸ�� ���� ���� �Լ�
	//����ȭ�� ������ ���� 1.0�� 100%
	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	bool bLMBDown;
	void LMBDown();
	void LMBUp();

	bool bESCDown;
	void ESCDown();
	void ESCUp();

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera;  }

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = Items)
	class AWeapon* EquippedWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = Items)
	class AItem* ActiveOverlappingItem;

	void SetEquippedWeapon(AWeapon* WeaponToSet);
	FORCEINLINE AWeapon* GetEquippedWeapon() {return EquippedWeapon ; }
	FORCEINLINE void SetActiveOverlappingItem(AItem* Item) { ActiveOverlappingItem = Item; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Anims")
	bool bAttacking;

	void Attack();

	UFUNCTION(BlueprintCallable)
	void AttackEnd();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anims")
	class UAnimMontage* CombatMontage;

	UFUNCTION(BlueprintCallable)
	void PlaySwingSound();

	UFUNCTION(BlueprintCallable)
	void DeathEnd();

	void UpdateCombatTarget();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	TSubclassOf<AEnemy> EnemyFilter;

	void SwitchLevel(FName LevelName);

	UFUNCTION(BlueprintCallable)
	void SaveGame();

	UFUNCTION(BlueprintCallable)
	void LoadGame(bool SetPosition);

	void LoadGameNoSwitch();

};
