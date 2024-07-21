// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class VClass : ModuleRules
{
	public VClass(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" , "UMG", "AudioMixer", "Networking" , "Voice", "UniversalVoiceChatPro", "HTTP" , "WebBrowser", "WebBrowserWidget"});

		//PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" , "Dollars" });
		
		string OpusPath = Path.Combine(ModuleDirectory, "ThirdParty", "opus-1.5.2");
		PublicIncludePaths.Add(Path.Combine(OpusPath, "include"));
		PublicAdditionalLibraries.Add(Path.Combine(OpusPath, "lib", "opus.lib"));
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}