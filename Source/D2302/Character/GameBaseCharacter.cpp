// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBaseCharacter.h"

#include "D2302/Backpack/BackpackComponent.h"
#include "D2302/Property/PropertyComponent.h"
#include "D2302/Shop/ShopComponent.h"
#include "D2302/Workmanship/WorkmanshipComponent.h"

AGameBaseCharacter::AGameBaseCharacter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	//AbilitySystemComponent = CreateDefaultSubobject<UGameAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	BackpackComponent = CreateDefaultSubobject<UBackpackComponent>(TEXT("BackpackComponent"));
	ShopComponent = CreateDefaultSubobject<UShopComponent>(TEXT("ShopComponent"));
	WorkmanshipComponent = CreateDefaultSubobject<UWorkmanshipComponent>(TEXT("WorkmanshipComponent"));
	PropertyComponent = CreateDefaultSubobject<UPropertyComponent>(TEXT("PropertyComponent"));
	
}

//UGameAbilitySystemComponent* AGameBaseCharacter::GetAbilitySystemComponent(){return AbilitySystemComponent;}
	
UBackpackComponent* AGameBaseCharacter::GetBackpackComponent(){return BackpackComponent;}

UShopComponent* AGameBaseCharacter::GetShopComponent(){return ShopComponent;}

UWorkmanshipComponent* AGameBaseCharacter::GetWorkmanshipComponent(){return WorkmanshipComponent;}

UPropertyComponent* AGameBaseCharacter::GetPropertyComponent(){return PropertyComponent;}