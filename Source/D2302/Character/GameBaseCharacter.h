// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "GameBaseCharacter.generated.h"

class UAbilitySystemComponent;
class UGameAbilitySystemComponent;
class UBackpackComponent;
class UShopComponent;
class UWorkmanshipComponent;
class UPropertyComponent;
/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class AGameBaseCharacter : public ACharacter//,public IAbilitySystemInterface
{
	GENERATED_BODY()

	
public:

	AGameBaseCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	//virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:

	//UPROPERTY(EditAnywhere,BlueprintReadOnly)
	//UGameAbilitySystemComponent* AbilitySystemComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UBackpackComponent* BackpackComponent;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UShopComponent* ShopComponent;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UWorkmanshipComponent* WorkmanshipComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UPropertyComponent* PropertyComponent;
public:
	
	//UGameAbilitySystemComponent* GetAbilitySystemComponent();
	
	UBackpackComponent* GetBackpackComponent();

	UShopComponent* GetShopComponent();

	UWorkmanshipComponent* GetWorkmanshipComponent();
	
	UPropertyComponent* GetPropertyComponent();
};
