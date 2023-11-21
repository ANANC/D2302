// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCommonFunctionLibrary.h"

#include "GameBaseInstance.h"
#include "Engine/GameEngine.h"
#include "D2302/Shop/ShopInstanceSubsystem.H"

UGameBaseInstance* UGameCommonFunctionLibrary::GetGameBaseInstance()
{
	UGameBaseInstance* GameInstance = nullptr;

	UGameEngine* engine = Cast<UGameEngine>(GEngine);
	if (engine)
	{
		UGameInstance* instance = engine->GameInstance;
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