// Fill out your copyright notice in the Description page of Project Settings.

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
	UPROPERTY(BlueprintReadOnly)
	FName PropName;
	
	UPROPERTY(BlueprintReadOnly)
	int Price;
	
	UPROPERTY(BlueprintReadOnly)
	int CurNumber;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FShopPropNumberUpdateDelegate,FName,shopName,FName,propName,int,number,int,price);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FShopSellPropDelegate,FName,shopName,FName,propName,int,number,int,price);

UCLASS(BlueprintType)
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
	class AGameBaseCharacter* Master;
	
	bool IsSetup{true};
	
	UPROPERTY(BlueprintReadOnly)
	TArray<UBaseShopProp*> ShopProps;
	
	UPROPERTY(BlueprintReadOnly)
	int Grade;

public:
	
	void SetShopName(FName shopName);
	
	UFUNCTION(BlueprintPure)
	FName GetShopName();

	void SetMaster(class AGameBaseCharacter* character);
	
	UFUNCTION(BlueprintPure)
	class AGameBaseCharacter* GetMaster();

	void InitShopByTableConfig();
	
	void AddProp(FName propName,int number,int price);

	void RemoveProp(FName propName,int number);

	UFUNCTION(BlueprintPure)
	bool CalculateSellPropCost(FName propName,int number,int& cost);
	
	bool SellProp(FName propName,int number);
	
	UFUNCTION(BlueprintPure)
	int GetPropNumber(FName propName);

protected:
	UBaseShopProp* GetShopProp(FName propName);
};
