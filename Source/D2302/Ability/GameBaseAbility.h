﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameplayAbility.h"
#include "GameBaseAbility.generated.h"

/**
 * 
 */
UCLASS()
class  UGameBaseAbility : public UGameplayAbility
{
	GENERATED_BODY()

	friend class UGameAbilitySystemComponent;

	
};
