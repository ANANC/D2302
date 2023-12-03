// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameCommonFunctionLibrary.generated.h"

class UGameBaseInstance;
class UShopInstanceSubsystem;
/**
 * 
 */
UCLASS()
class  UGameCommonFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure)
	static UGameBaseInstance* GetGameBaseInstance();
	
	UFUNCTION(BlueprintPure)
	static UShopInstanceSubsystem* GetShopInstanceSubsystem();

	UFUNCTION(BlueprintPure)
	static UPropInstanceSubsystem* GetPropInstanceSubsystem();
};
