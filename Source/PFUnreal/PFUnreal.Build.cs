// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PFUnreal : ModuleRules
{
	public PFUnreal(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Slate", "SlateCore", "AIModule" });
	}
}
