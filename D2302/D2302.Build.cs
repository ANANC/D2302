// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class D2302 : ModuleRules
{
	public D2302(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
		
		PublicDependencyModuleNames.AddRange(new string[] { "GameplayAbilities","GameplayTags","GameplayTasks" });

	}
}
