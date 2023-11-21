// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "TradeAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class D2302_API UTradeAttributeSet : public UBaseAttributeSet
{
	GENERATED_BODY()

public:
	UTradeAttributeSet();
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Money;
	ATTRIBUTE_ACCESSORS(UTradeAttributeSet, Money);
	
protected:
	
	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const;

	
};
