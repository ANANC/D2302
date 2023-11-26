// Fill out your copyright notice in the Description page of Project Settings.


#include "AIConsumptionComponent.h"

#include "D2302/Common/GameCommonFunctionLibrary.h"
#include "D2302/Shop/ShopInstanceSubsystem.h"
#include "D2302/Shop/ShopTypes.h"


// Sets default values for this component's properties
UAIConsumptionComponent::UAIConsumptionComponent()
{
}


// Called when the game starts
void UAIConsumptionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	ShopInstanceSubsystem = UGameCommonFunctionLibrary::GetShopInstanceSubsystem();
	
	if(AIConsumptionTable)
	{
		TArray<FAIConsumptionTableConfigData*> rows;
		AIConsumptionTable->GetAllRows(TEXT("FAIConsumptionTableConfigData"),rows);

		for(int index = 0;index<rows.Num();++index)
		{
			AIConsumptionTableConfigDatas.Add(*rows[index]);
		}
	}

	ConsumptionDesire = DefaultConsumptionDesire;
}

FShoppingList UAIConsumptionComponent::GetDesireShopShoppingList(FName shopName)
{
	FShoppingList shoppingList;
	
	if(!ShopInstanceSubsystem)
	{
		return shoppingList;
	}

	UBaseShop* shop = ShopInstanceSubsystem->GetShop(shopName);
	if(!shop)
	{
		return shoppingList;
	}

	FAIConsumptionDesireTableConfigData consumptionDesireConfig;
	if(!GetAIConsumptionDesireTableConfigData(ConsumptionDesire,consumptionDesireConfig))
	{
		return shoppingList;
	}

	int itemType = FMath::RandRange(consumptionDesireConfig.BuyItemTypeRange.X,consumptionDesireConfig.BuyItemTypeRange.Y);
	
	
}

bool UAIConsumptionComponent::GetAIConsumptionDesireTableConfigData(FName consumptionDesire,FAIConsumptionDesireTableConfigData& config)
{
	if(AIConsumptionDesireTable)
	{
		FAIConsumptionDesireTableConfigData* configPtr = AIConsumptionDesireTable->FindRow<FAIConsumptionDesireTableConfigData>(consumptionDesire,"FAIConsumptionDesireTableConfigData");
		if(configPtr)
		{
			config = *configPtr;
			return true;
		}
	}
	return false;
}