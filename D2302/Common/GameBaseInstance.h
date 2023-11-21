// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "GameBaseInstance.generated.h"

/**
 * 
 */
UCLASS()
class UGameBaseInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UGameBaseInstance(const FObjectInitializer& ObjectInitializer);

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UDataTable* ShopPropTable;	//FShopPropTableConfigData
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UDataTable* ShopTable;		//FShopTableConfigData
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UDataTable* PropTable;		//FPropTableConfigData
public:

	virtual void Init() override;
	virtual void Shutdown() override;
	virtual void LoadComplete(const float LoadTime, const FString& MapName) override;
};
