// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBaseInstance.h"

UGameBaseInstance::UGameBaseInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// do nothing
}

void UGameBaseInstance::Init()
{
	Super::Init();
}

void UGameBaseInstance::Shutdown()
{
	Super::Shutdown();
}

void UGameBaseInstance::LoadComplete(const float LoadTime, const FString& MapName)
{
	Super::LoadComplete(LoadTime, MapName);
}