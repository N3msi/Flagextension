class CfgPatches
{
	class nm_Flag
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Scripts",
			"DZ_Characters",
			"DZ_Gear_Camping",
			"DZ_Characters_Tops"
		};
	};
};
class CfgMods
{
	class nm_Flag
	{
		dir="nm_Flagextension";
		name="nm_Flagextension";
		credits="n3msi";
		author="n3msi";
		authorID="0";
		version="1.25";
		extra=0;
		type="mod";
	};
};

class cfgVehicles
{
	class Inventory_Base;
	class Flag_Base: Inventory_Base
	{
		scope=0;
		inventorySlot[]=
		{
			"Material_FPole_Flag",
			"Armband",
			"back"
		};
		itemInfo[]=
		{
			"Clothing",
			"Armband"
		};
		carveNavmesh = 1;
		itemBehaviour=1;
		physLayer = "item_small";
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{1,{""}},
						{0.69999999,{""}},
						{0.5,{""}},
						{0.30000001,{""}},
						{0,{""}}
					};
				};
			};
			class GlobalArmor
			{
				class Projectile
				{
					class Health{damage=0.94999999;};
					class Blood{damage=1;};
					class Shock{damage=1;};
				};
				class FragGrenade
				{
					class Health{damage=0.94999999;};
					class Blood{damage=1;};
					class Shock{damage=1;};
				};
				class Infected
				{
					class Health{damage=0.94999999;};
					class Blood{damage=1;};
					class Shock{damage=1;};
				};
				class Melee
				{
					class Health{damage=0.94999999;};
					class Blood{damage=1;};
					class Shock{damage=1;};
				};
			};
		};
	};
	class nm_Flag_deployed : Inventory_Base
	{
		scope = 2;
		displayName="$STR_CfgVehicles_Flag_Base0";
		descriptionShort="$STR_CfgVehicles_Flag_Base1";
		model="nm_Flagextension\flag\nm_Flag_deployed.p3d";
		overrideDrawArea="8.0";
		forceFarBubble="true";
		slopeTolerance=0.2;
		yawPitchRollLimit[]={45,45,45};
		destroyOnEmpty=0;
		varQuantityDestroyOnMin=0;
		quantityBar=1;
		carveNavmesh=1;
		canBeDigged=0;
		heavyItem=1;
		weight=10000;
		itemSize[]={2,2};
		repairableWithKits[]={};
		repairCosts[]={};
		itemBehaviour=0;
		absorbency=0.1;
		hiddenSelections[]=
		{
			"camo"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{1,{"nm_Flagextension\flag\data\nm_Flag_frame.rvmat"}},
						{0.69999999,{"nm_Flagextension\flag\data\nm_Flag_frame.rvmat"}},
						{0.5,{"nm_Flagextension\flag\data\nm_Flag_frame_damage.rvmat"}},
						{0.30000001,{"nm_Flagextension\flag\data\nm_Flag_frame_damage.rvmat"}},
						{0,{"nm_Flagextension\flag\data\nm_Flag_frame_destruct.rvmat"}}
					};
				};
			};
			class GlobalArmor
			{
				class Projectile
				{
					class Health{damage=0.94999999;};
					class Blood{damage=1;};
					class Shock{damage=1;};
				};
				class FragGrenade
				{
					class Health{damage=0.94999999;};
					class Blood{damage=1;};
					class Shock{damage=1;};
				};
				class Infected
				{
					class Health{damage=0.94999999;};
					class Blood{damage=1;};
					class Shock{damage=1;};
				};
				class Melee
				{
					class Health{damage=0.94999999;};
					class Blood{damage=1;};
					class Shock{damage=1;};
				};
			};
		};
	};
	class nm_Flag_Placing: nm_Flag_deployed
	{
		displayName="This is a hologram";
		descriptionShort="Nothing to see here, move along";
		model="nm_Flagextension\flag\nm_Flag_placing.p3d";
		alignHologramToTerain=0;
		slopeTolerance=0.30000001;
		storageCategory=10;
	};
	class Clothing_Base;
	class Clothing: Clothing_Base
	{
	};
	class nm_ArmbandDummy: Clothing
	{
		scope=2;
		displayName="$STR_CfgVehicles_Flag_Base0";
		descriptionShort="$STR_CfgVehicles_Flag_Base1";
		model="nm_Flagextension\flag\nm_ArmCapeDummy_g.p3d";
		inventorySlot[]=
		{
			"Material_FPole_Flag",
			"armband",
			"back"
		};
		attachments[]={};
		itemInfo[]=
		{
			"Clothing"
		};
		hiddenSelections[]=
		{
			"armband",
			"cape",
			"camo"
		};
		ragQuantity=6;
		rotationFlags=34;
		weight=50;
		itemSize[]={2,2};
		varWetMax=1;
		quickBarBonus=0;
		repairableWithKits[]={5,2};
		repairCosts[]={30,25};
		visibilityModifier=0.89999998;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{1,{""}},
						{0.69999999,{""}},
						{0.5,{""}},
						{0.30000001,{""}},
						{0,{""}}
					};
				};
			};
			class GlobalArmor
			{
				class Projectile
				{
					class Health{damage=0.94999999;};
					class Blood{damage=1;};
					class Shock{damage=1;};
				};
				class FragGrenade
				{
					class Health{damage=0.94999999;};
					class Blood{damage=1;};
					class Shock{damage=1;};
				};
				class Infected
				{
					class Health{damage=0.94999999;};
					class Blood{damage=1;};
					class Shock{damage=1;};
				};
				class Melee
				{
					class Health{damage=0.94999999;};
					class Blood{damage=1;};
					class Shock{damage=1;};
				};
			};
		};
		class ClothingTypes
		{
			male="nm_Flagextension\flag\nm_ArmCapeDummy_m.p3d";
			female="nm_Flagextension\flag\nm_ArmCapeDummy_f.p3d";
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUpItem
				{
					soundSet="Shirt_pickup_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="Shirt_drop_SoundSet";
					id=898;
				};
			};
		};
	};
	class nm_DoubleArmbandDummy: Clothing
	{
		Scope=2;
		displayName="$STR_CfgVehicles_Armband_ColorBase0";
		descriptionShort="$STR_CfgVehicles_Armband_ColorBase1";
		model="nm_Flagextension\flag\nm_DoubleABDummy_g.p3d";
		inventorySlot[]=
		{
			"Armband"
		};
		itemInfo[]=
		{
			"Clothing",
			"Armband"
		};
		rotationFlags=17;
		weight=50;
		itemSize[]={1,2};
		ragQuantity=2;
		varWetMax=1;
		repairableWithKits[]={5,2};
		repairCosts[]={30,25};
		visibilityModifier=0.94999999;
		hiddenSelections[]=
		{
			"small",
			"big",
			"camo"
		};		
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{
							1,
							{
							"nm_Flagextension\flag\data\nm_ArmbandDummy.rvmat", //doesnt work
							"nm_Flagextension\flag\data\nm_ArmbandDummy.rvmat",
							"nm_Flagextension\flag\data\nm_ArmbandDummy.rvmat"
							}
						},
						{
							0.69999999,
							{
							"nm_Flagextension\flag\data\nm_ArmbandDummy.rvmat",
							"nm_Flagextension\flag\data\nm_ArmbandDummy.rvmat",
							"nm_Flagextension\flag\data\nm_ArmbandDummy.rvmat"
							}
						},
						{
							0.5,
							{
							"nm_Flagextension\flag\data\nm_ArmbandDummy_damage.rvmat",
							"nm_Flagextension\flag\data\nm_ArmbandDummy_damage.rvmat",
							"nm_Flagextension\flag\data\nm_ArmbandDummy_damage.rvmat"
							}
						},
						{
							0.30000001,
							{
							"nm_Flagextension\flag\data\nm_ArmbandDummy_damage.rvmat",
							"nm_Flagextension\flag\data\nm_ArmbandDummy_damage.rvmat",
							"nm_Flagextension\flag\data\nm_ArmbandDummy_damage.rvmat"
							}
						},
						{
							0,
							{
							"nm_Flagextension\flag\data\nm_ArmbandDummy_destruct.rvmat",
							"nm_Flagextension\flag\data\nm_ArmbandDummy_destruct.rvmat",
							"nm_Flagextension\flag\data\nm_ArmbandDummy_destruct.rvmat"
							}
						}
					};
				};
			};
			class GlobalArmor
			{
				class Projectile
				{
					class Health{damage=0.94999999;};
					class Blood{damage=1;};
					class Shock{damage=1;};
				};
				class FragGrenade
				{
					class Health{damage=0.94999999;};
					class Blood{damage=1;};
					class Shock{damage=1;};
				};
				class Infected
				{
					class Health{damage=0.94999999;};
					class Blood{damage=1;};
					class Shock{damage=1;};
				};
				class Melee
				{
					class Health{damage=0.94999999;};
					class Blood{damage=1;};
					class Shock{damage=1;};
				};
			};
		};
		class ClothingTypes
		{
			male="nm_Flagextension\flag\nm_DoubleABDummy_m.p3d";
			female="nm_Flagextension\flag\nm_DoubleABDummy_f.p3d";
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUpItem
				{
					soundSet="Shirt_pickup_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="Shirt_drop_SoundSet";
					id=898;
				};
			};
		};
	};
};