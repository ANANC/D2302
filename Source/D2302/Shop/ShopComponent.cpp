// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopComponent.h"

#include "ShopInstanceSubsystem.h"
#include "D2302/Ability/GameAbilitySystemComponent.h"
#include "D2302/Ability/AttributeSet/TradeAttributeSet.h"
#include "D2302/Character/GameBaseCharacter.h"
#include "D2302/Common/GameCommonFunctionLibrary.h"


// Sets default values for this component's properties
UShopComponent::UShopComponent()
{
	
}


// Called when the game starts
void UShopComponent::BeginPlay()
{
	Super::BeginPlay();

	ShopInstanceSubsystem = UGameCommonFunctionLibrary::GetShopInstanceSubsystem();

	Character = Cast<UGameBaseCharacter>(GetOwner());
	
	LoadConfigShop();
}


void UShopComponent::LoadConfigShop()
{
	if(ShopInstanceSubsystem)
	{
		for(int index = 0;index<ShopNames.Num();++index)
		{
			UBaseShop* shop = ShopInstanceSubsystem->GetShop(ShopNames[index]);
			if(shop)
			{
				Shops.Add(shop);
			}
		}
	}
}

bool UShopComponent::BuyOtherShopProp(FName shopName,FName propNumber,int number)
{
	if(!ShopInstanceSubsystem)
	{
		return false;
	}

	UBaseShop* shop = ShopInstanceSubsystem->GetShop(shopName);
	if(!shop)
	{
		return false;
	}

	int cost;
	if(shop->SellPropCost(propNumber,number,cost))
	{
		int curMoney = Character->GetAbilitySystemComponent()->GetNumericAttribute(UTradeAttributeSet::GetMoneyAttribute());
		if(curMoney >= cost)
		{
			
		}
		return true;
	}

	return false;
}

bool UShopComponent::SellMyShopProp(FName propName,int number)
{
	
}
