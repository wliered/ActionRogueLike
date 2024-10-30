// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "ActionRogueLike/Characters/CharacterComponents/Rogue_InteractionComponent.h"
#include "GameFramework/Character.h"
#include "Rogue_Character.generated.h"

class ARogue_MagicProjectile;
class UInputAction;
class UInputMappingContext;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class ACTIONROGUELIKE_API ARogue_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARogue_Character();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PrimaryAttackAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SecondaryAttackAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* TeleportAction;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(EditAnywhere, Category = Combat)
	TSubclassOf<ARogue_MagicProjectile> PrimaryAttackProjectileClass;
	UPROPERTY(EditAnywhere, Category = Combat)
	TSubclassOf<ARogue_MagicProjectile> SecondaryAttackProjectileClass;
	UPROPERTY(EditAnywhere, Category = Combat)
	TSubclassOf<ARogue_MagicProjectile> TeleportingProjectileClass;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<URogue_InteractionComponent> InteractionComponent;
	UPROPERTY(EditAnywhere, Category=Combat)
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditAnywhere)
	bool bDebugCameraLineTrace;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void JumpUp(const FInputActionValue& Value);
	void PrimaryAttack(const FInputActionValue& Value);
	void SecondaryAttack(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);
	void Teleport(const FInputActionValue& Value);

	FRotator GetProjectileRotation(FVector SpawnLocation);

	void PrimaryAttack_TimeElapsed();
	void SecondaryAttack_TimeElapsed();
	void TeleportProjectile_TimeElapsed();
	
	void FireProjectile(const TSubclassOf<ARogue_MagicProjectile>& ProjectileClass);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};
