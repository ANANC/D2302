// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AIConsumptionTypes.generated.h"

USTRUCT(BlueprintType)
struct FAIConsumptionDesireTableConfigData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool HasConsumptionLimit;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,meta=(ClampMin = 0,UIMin = 0,ClampMax =1,UIMax = 1))
	float ItemTypeProportion;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,meta=(ClampMin = 0,UIMin = 0,ClampMax =1,UIMax = 1))
	float ItemNumberProportion;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,meta=(ClampMin = 0,UIMin = 0,ClampMax =1,UIMax = 1))
	float ItemMoneyProportion;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FVector2D BuyItemTypeRange;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FVector2D BuyItemNumberRange;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FVector2D BuyTotalMoneyRange;
};

USTRUCT(BlueprintType)
struct FAIConsumptionTableConfigData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName PropName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,meta=(ClampMin = 0,UIMin = 0,ClampMax =1,UIMax = 1))
	float Desire{1};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,meta=(ClampMin = 0,UIMin = 0,ClampMax =1,UIMax = 1))
	bool HasSingleBuyLimit{true};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,meta=(ClampMin = 0,UIMin = 0,ClampMax =1,UIMax = 1))
	int MaxSingleBuyNumber{2};
};


USTRUCT()
struct FShoppingItem
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	FName PropName;
	
	UPROPERTY(BlueprintReadWrite)
	int Number;
};

USTRUCT()
struct FShoppingList
{
	GENERATED_BODY()
public:
	TArray<FShoppingItem> ShoppingItems;
};