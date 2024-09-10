class CfgPatches
{
	class nm_Flagextension
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Scripts"
		};
	};
};
class CfgMods
{
	class nm_Flagextension
	{
		dir="nm_Flagextension";
		name="nm_Flagextension";
		credits="n3msi & Buddy";
		author="n3msi & Buddy";
		authorID="0";
		version="1.25";
		extra=0;
		type="mod";
		dependencies[]=
		{
			"World"
		};
		class defs
		{
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"nm_Flagextension/scripts/4_World"
				};
			};
		};
	};
};