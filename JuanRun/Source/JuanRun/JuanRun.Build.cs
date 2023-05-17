// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class JuanRun : ModuleRules
{
	public JuanRun(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });

        PublicDependencyModuleNames.AddRange(new string[] { "OnlineSubsystem", "OnlineSubsystemEOS", "OnlineSubsystemUtils", "OnlineSubsystemNull" });
        //PublicDependencyModuleNames.AddRange(new string[] { "OnlineSubsystem", "OnlineSubsystemEOS", "OnlineSubsystemUtils", "OnlineSubsystemNull" });
    }
}
