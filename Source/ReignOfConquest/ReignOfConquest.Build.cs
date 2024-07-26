// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ReignOfConquest : ModuleRules
{
	public ReignOfConquest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
