// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAttributeSet.h"

#include "GameAbilitySystemComponent.h"

UBaseAttributeSet::UBaseAttributeSet()
{
}

UWorld* UBaseAttributeSet::GetWorld() const
{
	const UObject* Outer = GetOuter();
	check(Outer);

	return Outer->GetWorld();
}

UGameAbilitySystemComponent* UBaseAttributeSet::GetLyraAbilitySystemComponent() const
{
	return Cast<UGameAbilitySystemComponent>(GetOwningAbilitySystemComponent());
}

