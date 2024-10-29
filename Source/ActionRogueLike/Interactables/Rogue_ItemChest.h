// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionRogueLike/Interfaces/Rogue_GameplayInterface.h"
#include "GameFramework/Actor.h"
#include "Rogue_ItemChest.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ARogue_ItemChest : public AActor, public IRogue_GameplayInterface
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float TargetPitch;
	
	void Interact_Implementation(APawn* InstigatorPawn) override;

public:
	// Sets default values for this actor's properties
	ARogue_ItemChest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> LidMesh;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
