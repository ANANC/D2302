


#include "WorkmanshipComponent.h"

#include "WorkmanshipTypes.h"
#include "Engine/DataTable.h"


// Sets default values for this component's properties
UWorkmanshipComponent::UWorkmanshipComponent()
{
	// ...
}


// Called when the game starts
void UWorkmanshipComponent::BeginPlay()
{
	Super::BeginPlay();

	InitWorkmanship();
}

void UWorkmanshipComponent::InitWorkmanship()
{
	if(!WorkmanshipTable)
	{
		return;
	}

	WorkmanshipTable->GetAllRows<FWorkmanshipTableConfigData>(TEXT("FWorkmanshipTableConfigData"),WorkmanshipConfigInfos);

	for(int index = 0;index<WorkmanshipConfigInfos.Num();++index)
	{
		FWorkmanshipTableConfigData* row = WorkmanshipConfigInfos[index];

		UWorkmanshipInfo* info = NewObject<UWorkmanshipInfo>(this);
		info->WorkmanshipType = row->WorkmanshipType;
		info->CurGrade = row->DefaultGrade;

		WorkmanshipInfos.Add(info);
	}
	
	for(int index = 0;index<WorkmanshipInfos.Num();++index)
	{
		UWorkmanshipInfo* config = WorkmanshipInfos[index];
		config->IsActive = IsWorkmanshipEnableActive(config->WorkmanshipType);
	}
}

bool UWorkmanshipComponent::IsWorkmanshipEnableActive(EWorkmanshipType workmanshipType)
{
	FWorkmanshipTableConfigData config;
	if(!GetWorkmanshipTableConfigData(workmanshipType,config))
	{
		return false;
	}

	bool enable = false;

	if(config.Precondition.Num() == 0)
	{
		enable = true;
	}else
	{
		enable = true;
		for(TMap<EWorkmanshipType,int>::TConstIterator iter = config.Precondition.CreateConstIterator();iter;++iter)
		{
			EWorkmanshipType preconditionType = iter.Key();
			int preconditionGrade = iter.Value();

			UWorkmanshipInfo* preconditionInfo = GetWorkmanshipInfo(preconditionType);
			if(!preconditionInfo)
			{
				enable = false;
				break;
			}

			if(preconditionInfo->CurGrade<preconditionGrade)
			{
				enable = false;
				break;
			}
		}
	}
	return enable;
}

UWorkmanshipInfo* UWorkmanshipComponent::GetWorkmanshipInfo(EWorkmanshipType workmanshipType)
{
	for(int index = 0;index<WorkmanshipInfos.Num();++index)
	{
		UWorkmanshipInfo* config = WorkmanshipInfos[index];
		if(config->WorkmanshipType == workmanshipType)
		{
			return config;
		}
	}

	return nullptr;
}

bool UWorkmanshipComponent::GetWorkmanshipTableConfigData(EWorkmanshipType workmanshipType,FWorkmanshipTableConfigData& data)
{
	for(int index = 0;index<WorkmanshipConfigInfos.Num();++index)
	{
		FWorkmanshipTableConfigData* config = WorkmanshipConfigInfos[index];
		if(config->WorkmanshipType == workmanshipType)
		{
			data = *config;
			return true;
		}
	}

	return false;
}

bool UWorkmanshipComponent::GetWorkmanshipActive(EWorkmanshipType workmanshipType)
{
	UWorkmanshipInfo* preconditionInfo = GetWorkmanshipInfo(workmanshipType);
	if(!preconditionInfo)
	{
		return false;
	}

	return preconditionInfo->IsActive;
}