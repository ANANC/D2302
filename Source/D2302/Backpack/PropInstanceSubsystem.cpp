// Fill out your copyright notice in the Description page of Project Settings.


#include "PropInstanceSubsystem.h"

#include "D2302/Common/GameBaseInstance.h"

void UPropInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	
}

void UPropInstanceSubsystem::Deinitialize()

{
	
}

bool UPropInstanceSubsystem::GetPropConfigableInfo(FName propName,FPropTableConfigData& config)
{
	UGameBaseInstance* instance = Cast<UGameBaseInstance>(GetGameInstance());
	if(instance && instance->PropTable)
	{
		FPropTableConfigData* configPtr = instance->PropTable->FindRow<FPropTableConfigData>(propName,"FPropTableConfigData");
		if(configPtr)
		{
			config = *configPtr;
			return true;
		}
	}
	return false;
}