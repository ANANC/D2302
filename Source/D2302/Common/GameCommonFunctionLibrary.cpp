// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCommonFunctionLibrary.h"

#include "GameBaseInstance.h"
#include "KismetTraceUtils.h"
#include "Engine/GameEngine.h"
#include "D2302/Shop/ShopInstanceSubsystem.H"

UGameBaseInstance* UGameCommonFunctionLibrary::GetGameBaseInstance()
{
	UGameBaseInstance* GameInstance = nullptr;
	
	if (GWorld && GWorld->GetWorld())
	{
		UGameInstance* instance = GWorld->GetWorld()->GetGameInstance();
		if(instance)
		{
			GameInstance = Cast<UGameBaseInstance>(instance);
		}
	}

	return GameInstance;
}

UShopInstanceSubsystem* UGameCommonFunctionLibrary::GetShopInstanceSubsystem()
{
	UGameBaseInstance* instance = GetGameBaseInstance();
	if(instance)
	{
		return instance->GetSubsystem<UShopInstanceSubsystem>();
	}
	return nullptr;
}

UPropInstanceSubsystem* UGameCommonFunctionLibrary::GetPropInstanceSubsystem()
{
	UGameBaseInstance* instance = GetGameBaseInstance();
	if(instance)
	{
		return instance->GetSubsystem<UPropInstanceSubsystem>();
	}
	return nullptr;
}