// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ShopTypes.h"
#include "ShopInstanceSubsystem.generated.h"

class UBaseShop;

/**
 * 
 */
UCLASS()
class  UShopInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

protected:
	
	UPROPERTY()
	TArray<UBaseShop*> ValidShops;

public:
	UFUNCTION(BlueprintPure)
	UBaseShop* GetShop(FName shopName);
	
	UFUNCTION(BlueprintPure)
	bool GetShopConfigTableInfo(FName shopName,FShopTableConfigData& config);
	
	UFUNCTION(BlueprintPure)
	bool GetShopPropConfigTableInfo(FName shopPropName,FShopPropTableConfigData& config);
protected:
	UBaseShop* CreateShop(FName shopName);

	UBaseShop* FindValidShop(FName shopName);
};
