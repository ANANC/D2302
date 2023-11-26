// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AIConsumptionTypes.h"
#include "AIConsumptionComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class D2302_API UAIConsumptionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAIConsumptionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UDataTable* AIConsumptionTable;	//FAIConsumptionTableConfigData
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UDataTable* AIConsumptionDesireTable; //FAIConsumptionDesireTableConfigData
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName DefaultConsumptionDesire;
	
protected:
	
	UPROPERTY()
	class UShopInstanceSubsystem* ShopInstanceSubsystem;
	
	UPROPERTY()
	TArray<FAIConsumptionTableConfigData> AIConsumptionTableConfigDatas;

	FName ConsumptionDesire;
	
public:

	UPROPERTY()
	FShoppingList GetDesireShopShoppingList(FName shopName);

	bool GetAIConsumptionDesireTableConfigData(FName consumptionDesire,FAIConsumptionDesireTableConfigData& config);
};
