// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopTypes.h"

void UBaseShop::SetShopName(FName shopName)
{
	ShopName = shopName;
}

FName UBaseShop::GetShopName()
{
	return ShopName;
}

void UBaseShop::InitShopByTableConfig()
{
	for(TMap<FName,FShopPropTableConfigData>::TConstIterator iter = ShopPropConfigs;iter;++iter)
	{
		FName propName = iter.Key();
		FShopPropTableConfigData config = iter.Value();

		if(config.SellDefaultNumber>0)
		{
			AddProp(propName,config.SellDefaultNumber,config.Price);
		}
	}
}

void UBaseShop::AddProp(FName propName,int number,int price)
{
	UBaseShopProp* shopProp = GetShopProp(propName);
	if(!shopProp)
	{
		shopProp = NewObject<UBaseShopProp>();
		shopProp->PropName = propName;
		shopProp->CurNumber = 0;
		shopProp->Price = price;

		ShopProps.Add(shopProp);
	}

	shopProp->CurNumber+=number;
	
	ShopPropNumberUpdateDelegate.Broadcast(ShopName,propName,shopProp->CurNumber,price);
}

void UBaseShop::RemoveProp(FName propName,int number)
{
	UBaseShopProp* shopProp = GetShopProp(propName);
	if(!shopProp)
	{
		return;
	}
	shopProp->CurNumber-=number;
	shopProp->CurNumber = shopProp->CurNumber>=0? shopProp->CurNumber:0;
	
	ShopPropNumberUpdateDelegate.Broadcast(ShopName,propName,shopProp->CurNumber,shopProp->Price);
}

void UBaseShop::SellProp(FName propName,int number)
{
	UBaseShopProp* shopProp = GetShopProp(propName);
	if(!shopProp)
	{
		return;
	}
	int sellNumber = shopProp->CurNumber>=number?number:shopProp->CurNumber;
	shopProp->CurNumber-=sellNumber;

	ShopPropNumberUpdateDelegate.Broadcast(ShopName,propName,shopProp->CurNumber,shopProp->Price);

	int sellPrice = shopProp->Price * sellNumber;
	ShopSellPropDelegate.Broadcast(ShopName,propName,shopProp->CurNumber,sellPrice);
}

UBaseShopProp* UBaseShop::GetShopProp(FName propName)
{
	for(int index = 0;index<ShopProps.Num();++index)
	{
		if(ShopProps[index]->PropName == propName)
		{
			return ShopProps[index];
		}
	}
	return nullptr;
}