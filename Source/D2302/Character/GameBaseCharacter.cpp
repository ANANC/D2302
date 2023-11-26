﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBaseCharacter.h"

#include "D2302/Ability/GameAbilitySystemComponent.h"
#include "D2302/Backpack/BackpackComponent.h"
#include "D2302/Property/PropertyComponent.h"
#include "D2302/Shop/ShopComponent.h"
#include "D2302/Workmanship/WorkmanshipComponent.h"

UGameBaseCharacter::UGameBaseCharacter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	//AbilitySystemComponent = CreateDefaultSubobject<UGameAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	BackpackComponent = CreateDefaultSubobject<UBackpackComponent>(TEXT("BackpackComponent"));
	ShopComponent = CreateDefaultSubobject<UShopComponent>(TEXT("ShopComponent"));
	WorkmanshipComponent = CreateDefaultSubobject<UWorkmanshipComponent>(TEXT("WorkmanshipComponent"));
	PropertyComponent = CreateDefaultSubobject<UPropertyComponent>(TEXT("PropertyComponent"));
	
}

//UGameAbilitySystemComponent* UGameBaseCharacter::GetAbilitySystemComponent(){return AbilitySystemComponent;}
	
UBackpackComponent* UGameBaseCharacter::GetBackpackComponent(){return BackpackComponent;}

UShopComponent* UGameBaseCharacter::GetShopComponent(){return ShopComponent;}

UWorkmanshipComponent* UGameBaseCharacter::GetWorkmanshipComponent(){return WorkmanshipComponent;}

UPropertyComponent* UGameBaseCharacter::GetPropertyComponent(){return PropertyComponent;}