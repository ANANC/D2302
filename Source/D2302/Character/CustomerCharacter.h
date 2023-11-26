// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameBaseCharacter.h"
#include "CustomerCharacter.generated.h"

class UAIConsumptionComponent;

UCLASS()
class D2302_API UCustomerCharacter : public UGameBaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UCustomerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(BlueprintReadOnly)
	UAIConsumptionComponent* AIConsumptionComponent;

public:
	
	UAIConsumptionComponent* GetAIConsumptionComponent();
};
