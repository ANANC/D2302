﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/Object.h"
#include "ShopTypes.generated.h"


USTRUCT(BlueprintType)
struct FShopPropTableConfigData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName TitleName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName PropName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Price;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName ShopName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int SellDefaultNumber;
};

USTRUCT(BlueprintType)
struct FShopTableConfigData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName TitleName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int DefaultGrade;
};



UCLASS()
class UBaseShopProp : public UObject
{
	GENERATED_BODY()

public:
	FName PropName;

	int Price;

	int CurNumber;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FShopPropNumberUpdateDelegate,FName,shopName,FName,propName,int,number,int,price);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FShopSellPropDelegate,FName,shopName,FName,propName,int,number,int,price);

UCLASS()
class UBaseShop : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FShopPropNumberUpdateDelegate ShopPropNumberUpdateDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FShopSellPropDelegate ShopSellPropDelegate;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FShopTableConfigData ShopConfig;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TMap<FName,FShopPropTableConfigData> ShopPropConfigs;
	
protected:
	FName ShopName;

	UPROPERTY(BlueprintReadOnly)
	class UGameBaseCharacter* Master;
	
	bool IsSetup{true};
	
	UPROPERTY()
	TArray<UBaseShopProp*> ShopProps;

	int Grade;

public:
	void SetShopName(FName shopName);

	FName GetShopName();

	void SetMaster(class UGameBaseCharacter* character);

	class UGameBaseCharacter* GetMaster();

	void InitShopByTableConfig();
	
	void AddProp(FName propName,int number,int price);

	void RemoveProp(FName propName,int number);

	UFUNCTION(BlueprintPure)
	bool CalculateSellPropCost(FName propName,int number,int& cost);
	
	bool SellProp(FName propName,int number);

	int GetPropNumber(FName propName);

protected:
	UBaseShopProp* GetShopProp(FName propName);
};
