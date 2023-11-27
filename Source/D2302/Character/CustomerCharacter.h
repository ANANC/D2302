// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameBaseCharacter.h"
#include "CustomerCharacter.generated.h"

class UAIConsumptionComponent;

UCLASS(Blueprintable,BlueprintType)
class ACustomerCharacter : public AGameBaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACustomerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UAIConsumptionComponent* AIConsumptionComponent;

public:
	
	UAIConsumptionComponent* GetAIConsumptionComponent();
};
