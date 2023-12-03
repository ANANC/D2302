// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopInstanceSubsystem.h"

#include "ShopTypes.h"
#include "D2302/Common/GameBaseInstance.h"

void UShopInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	
}

void UShopInstanceSubsystem::Deinitialize()
{
	
}

UBaseShop* UShopInstanceSubsystem::CreateShop(class AGameBaseCharacter* character,FName shopName)
{
	UBaseShop* shop = FindValidShop(shopName);
	if(shop)
	{
		return shop;
	}
	
	shop = CreateShop(shopName);
	if(shop)
	{
		shop->SetMaster(character);
	}

	return shop;
}

UBaseShop* UShopInstanceSubsystem::GetShop(FName shopName)
{
	UBaseShop* shop = FindValidShop(shopName);
	return shop;
}

UBaseShop* UShopInstanceSubsystem::CreateShop(FName shopName)
{
	UBaseShop* shop = NewObject<UBaseShop>();
	shop->SetShopName(shopName);

	UGameBaseInstance* instance = Cast<UGameBaseInstance>(GetGameInstance());
	if(instance && instance->ShopTable && instance->ShopPropTable)
	{
		FShopTableConfigData* configPtr = instance->ShopTable->FindRow<FShopTableConfigData>(shopName,"FShopTableConfigData");
		if(configPtr)
		{
			shop->ShopConfig = *configPtr;
		}

		TMap<FName,uint8*> shopPropRows = instance->ShopPropTable->GetRowMap();
		for(TMap<FName,uint8*>::TConstIterator iter = shopPropRows;iter;++iter)
		{
			FName shopPropName = iter->Key;
			FShopPropTableConfigData* config = (FShopPropTableConfigData*)(iter->Value);

			if(config && config->ShopName == shopName)
			{
				shop->ShopPropConfigs.Add(shopPropName,*config);
			}
		}
	}

	shop->InitShopByTableConfig();

	ValidShops.Add(shop);
	
	return shop;
}

UBaseShop* UShopInstanceSubsystem::FindValidShop(FName shopName)
{
	for(int index = 0;index <ValidShops.Num();++index)
	{
		if(ValidShops[index]->GetShopName() == shopName)
		{
			return ValidShops[index];
		}
	}

	return nullptr;
}

bool UShopInstanceSubsystem::GetShopConfigTableInfo(FName shopName,FShopTableConfigData& config)
{
	UGameBaseInstance* instance = Cast<UGameBaseInstance>(GetGameInstance());
	if(instance && instance->ShopTable)
	{
		FShopTableConfigData* configPtr = instance->ShopTable->FindRow<FShopTableConfigData>(shopName,"FShopTableConfigData");
		if(configPtr)
		{
			config = *configPtr;
			return true;
		}
	}
	return false;
}

bool UShopInstanceSubsystem::GetShopPropConfigTableInfo(FName shopPropName,FShopPropTableConfigData& config)
{
	UGameBaseInstance* instance = Cast<UGameBaseInstance>(GetGameInstance());
	if(instance && instance->ShopPropTable)
	{
		FShopPropTableConfigData* configPtr = instance->ShopPropTable->FindRow<FShopPropTableConfigData>(shopPropName,"FShopPropTableConfigData");
		if(configPtr)
		{
			config = *configPtr;
			return true;
		}
	}
	return false;
}