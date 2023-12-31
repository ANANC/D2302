﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopTypes.h"

void UBaseShop::SetShopName(FName shopName)
{
	ShopName = shopName;
}

FName UBaseShop::GetShopName()
{
	return ShopName;
}

void UBaseShop::SetMaster(class AGameBaseCharacter* character)
{
	Master = character;
}

class AGameBaseCharacter* UBaseShop::GetMaster()
{
	return Master;
}

void UBaseShop::InitShopByTableConfig()
{
	for(TMap<FName,FShopPropTableConfigData>::TConstIterator iter = ShopPropConfigs;iter;++iter)
	{
		FShopPropTableConfigData config = iter.Value();
		FName propName = config.PropName;

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

bool UBaseShop::CalculateSellPropCost(FName propName,int number,int& cost)
{
	UBaseShopProp* shopProp = GetShopProp(propName);
	if(!shopProp)
	{
		return false;
	}

	cost = shopProp->Price * number;
	return true;
}

bool UBaseShop::SellProp(FName propName,int number)
{
	UBaseShopProp* shopProp = GetShopProp(propName);
	if(!shopProp)
	{
		return false;
	}

	if(shopProp->CurNumber < number)
	{
		return false;
	}

	shopProp->CurNumber-=number;

	ShopPropNumberUpdateDelegate.Broadcast(ShopName,propName,shopProp->CurNumber,shopProp->Price);

	int sellPrice = shopProp->Price * number;
	ShopSellPropDelegate.Broadcast(ShopName,propName,shopProp->CurNumber,sellPrice);

	return true;
}

int UBaseShop::GetPropNumber(FName propName)
{
	UBaseShopProp* shopProp = GetShopProp(propName);
	if(!shopProp)
	{
		return 0;
	}

	return shopProp->CurNumber;
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