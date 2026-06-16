using UnrealBuildTool;

public class NumberBaseball : ModuleRules
{
	public NumberBaseball(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput",
			
			// UI
			"UMG","Slate", "SlateCore",
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
