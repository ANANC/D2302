// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BackpackTypes.h"
#include "PropInstanceSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class D2302_API UPropInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()


public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

public:
	
	UFUNCTION(BlueprintPure)
	bool GetPropConfigableInfo(FName propName,FPropTableConfigData& config);
};
