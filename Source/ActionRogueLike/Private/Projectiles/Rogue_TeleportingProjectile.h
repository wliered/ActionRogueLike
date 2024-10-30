// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectiles/Rogue_MagicProjectile.h"
#include "Rogue_TeleportingProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ARogue_TeleportingProjectile : public ARogue_MagicProjectile
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARogue_TeleportingProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UNiagaraComponent> ExplodeEffectComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TeleportTimerLength = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ExplodeTimerLength = .5f;

	void TeleportTimer_Elapsed();
	void ExplodeTimer_Elapsed();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
