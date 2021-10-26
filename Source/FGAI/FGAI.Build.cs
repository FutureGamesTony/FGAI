// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FGAI : ModuleRules
{
	public FGAI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
		PublicIncludePaths.Add("FGAI");
		PublicIncludePaths.Add("FGAI/AI");
		PublicIncludePaths.Add("FGAI/AI/Sensing");
		PublicIncludePaths.Add("FGAI/Components");
		PublicIncludePaths.Add("FGAI/Components/Weapons");


	}
}
