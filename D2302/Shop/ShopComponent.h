﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShopComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class D2302_API UShopComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UShopComponent();

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<FName> ShopNames;

protected:
	UPROPERTY()
	class UShopInstanceSubsystem* ShopInstanceSubsystem;

	UPROPERTY()
	TArray<class UBaseShop*> Shops;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	void BuyShopProp(FName propNumber,int number);
	
protected:
	void LoadConfigShop();
};