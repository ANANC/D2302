// Fill out your copyright notice in the Description page of Project Settings.


#include "AIConsumptionComponent.h"

#include "D2302/Character/GameBaseCharacter.h"
#include "D2302/Common/GameCommonFunctionLibrary.h"
#include "D2302/Property/PropertyComponent.h"
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

	AIConsumptionTableConfigDatas.Sort([](const FAIConsumptionTableConfigData& left,const FAIConsumptionTableConfigData& right)
	{
		return left.Desire>=right.Desire;
	});

	ConsumptionDesire = DefaultConsumptionDesire;
}

FShoppingList UAIConsumptionComponent::GetDesireShopShoppingList(FName shopName)
{
	FShoppingList shoppingList;
	shoppingList.ShopName = shopName;
	
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
	
	if(AIConsumptionTableConfigDatas.Num() == 0)
	{
		return shoppingList;
	}

	int itemType = FMath::RandRange(consumptionDesireConfig.BuyItemTypeRange.X,consumptionDesireConfig.BuyItemTypeRange.Y);
	if (itemType == 0){return shoppingList; }

	int maxMoneyLimit = consumptionDesireConfig.HasConsumptionLimit? -1:FMath::RandRange(consumptionDesireConfig.BuyTotalMoneyRange.X,consumptionDesireConfig.BuyTotalMoneyRange.Y);
	int curBuyMoney = 0;
	
	for(int index = 0;index<AIConsumptionTableConfigDatas.Num();++index)
	{
		FAIConsumptionTableConfigData consumptionConfig = AIConsumptionTableConfigDatas[index];
		
		FShoppingItem item;
		item.PropName = consumptionConfig.PropName;
		
		int itemNumberLimit = consumptionConfig.HasSingleBuyLimit?consumptionConfig.MaxSingleBuyNumber: FMath::RandRange(consumptionDesireConfig.BuyItemNumberRange.X,consumptionDesireConfig.BuyItemNumberRange.Y);
		for(int j = 0;j<itemNumberLimit;++j)
		{
			int cost;
			if(shop->CalculateSellPropCost(consumptionConfig.PropName,1,cost))
			{
				if(maxMoneyLimit!=-1 && curBuyMoney>cost)
				{
					break;
				}
				
				curBuyMoney += cost;
				item.Number += 1;
			}
		}

		if(item.Number>0)
		{
			shoppingList.ShoppingItems.Add(item);
		}
	}

	return shoppingList;
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

void UAIConsumptionComponent::Consumption(FName shopName)
{
	if(!ShopInstanceSubsystem)
	{
		return;
	}

	UBaseShop* shop = ShopInstanceSubsystem->GetShop(shopName);
	if(!shop)
	{
		return;
	}
	
	FShoppingList shoppingList = GetDesireShopShoppingList(shopName);
	for(int index = 0;index<shoppingList.ShoppingItems.Num();++index)
	{
		FShoppingItem item = shoppingList.ShoppingItems[index];

		int curShopItemNumber = shop->GetPropNumber(item.PropName);
		int buyNumber = curShopItemNumber>=item.Number?item.Number:curShopItemNumber;
		if(buyNumber>0)
		{
			int cost;
			if(shop->CalculateSellPropCost(item.PropName,buyNumber,cost))
			{
				if(shop->SellProp(item.PropName,buyNumber))
				{
					AGameBaseCharacter* master = shop->GetMaster();
					if(master)
					{
						master->GetPropertyComponent()->PropertyValueAddValue(PropertyName::Money,cost);
					}
				}
			}
		}
	}
}