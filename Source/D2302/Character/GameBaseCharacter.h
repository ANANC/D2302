// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularCharacter.h"
#include "UObject/Object.h"
#include "AbilitySystemInterface.h"
#include "GameBaseCharacter.generated.h"

class UAbilitySystemComponent;
class UGameAbilitySystemComponent;
class UBackpackComponent;
class UShopComponent;
class UWorkmanshipComponent;

/**
 * 
 */
UCLASS()
class D2302_API UGameBaseCharacter : public AModularCharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()

	
public:

	UGameBaseCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UGameAbilitySystemComponent* AbilitySystemComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UBackpackComponent* BackpackComponent;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UShopComponent* ShopComponent;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UWorkmanshipComponent* WorkmanshipComponent;

public:
	
	UGameAbilitySystemComponent* GetAbilitySystemComponent();
	
	UBackpackComponent* GetBackpackComponent();

	UShopComponent* GetShopComponent();

	UWorkmanshipComponent* GetWorkmanshipComponent();
};
