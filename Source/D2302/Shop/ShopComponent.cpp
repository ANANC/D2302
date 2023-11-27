// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopComponent.h"

#include "ShopInstanceSubsystem.h"
#include "D2302/Backpack/BackpackComponent.h"
#include "D2302/Character/GameBaseCharacter.h"
#include "D2302/Common/GameCommonFunctionLibrary.h"
#include "D2302/Property/PropertyComponent.h"


// Sets default values for this component's properties
UShopComponent::UShopComponent()
{
	
}


// Called when the game starts
void UShopComponent::BeginPlay()
{
	Super::BeginPlay();

	ShopInstanceSubsystem = UGameCommonFunctionLibrary::GetShopInstanceSubsystem();

	Character = Cast<AGameBaseCharacter>(GetOwner());
	
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
				shop->SetMaster(Character);
				
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
	if(shop->CalculateSellPropCost(propNumber,number,cost))
	{
		UPropertyComponent* propertyComponent = Character->GetPropertyComponent();
		if(propertyComponent->GetPropertyValueEqualorGreaterthanTargetValue(PropertyName::Money,cost))
		{
			if(propertyComponent->TransferMyValueToAnotherCharacter(shop->GetMaster(),PropertyName::Money,cost))
			{
				shop->SellProp(propNumber,number);

				UBackpackComponent* backpackComponent = Character->GetBackpackComponent();
				backpackComponent->AddPorp(propNumber,number);
				
				return true;
			}
		}
	}

	return false;
}

