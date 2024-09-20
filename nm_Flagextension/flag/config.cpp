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
			"DZ_Characters_Tops",
			"DZ_Gear_Crafting",
			"DZ_Vehicles_Wheeled"
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
		hiddenSelections[]=
		{
			"camo"
		};
		hiddenSelectionsTextures[]=
		{
			"dz\gear\camping\data\flag_chern_co.paa"
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
	class nm_DoubleArmbandRCDummy: nm_DoubleArmbandDummy
	{
		Scope=2;
	};
	class nm_BandanaDummy: Clothing
	{
		scope=2;
		displayName="$STR_cfgvehicles_bandana_colorbase0";
		descriptionShort="$STR_cfgvehicles_bandana_colorbase1";
		model="nm_Flagextension\flag\nm_BandanaHybrid_g.p3d";
		simulation="clothing";
		vehicleClass="Clothing";
		itemInfo[]=
		{
			"Clothing",
			"Headgear"
		};
		visibilityModifier=0.89999998;
		inventorySlot[]=
		{
			"Headgear",
			"Mask"
		};
		rotationFlags=34;
		weight=120;
		itemSize[]={3,1};
		ragQuantity=1;
		varWetMax=1;
		heatIsolation=0.40000001;
		repairableWithKits[]={5,2};
		repairCosts[]={30,25};
		headSelectionsToHide[]=
		{
			"Clipping_BandanaHead",
			"Clipping_BandanaFace"
		};
		hiddenSelections[]=
		{
			"hat",
			"mask",
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
			male="nm_Flagextension\flag\nm_BandanaHybrid_m.p3d";
			female="nm_Flagextension\flag\nm_BandanaHybrid_f.p3d";
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
	class nm_BandanaRCDummy: nm_BandanaDummy
	{
		scope=2;
	};
	class nm_SlingbagDummy: Clothing
	{
		scope=2;
		displayName="$STR_nmSlingbagDummy";
		descriptionShort="$STR_nmSlingbagDummyDISC";
		model="nm_Flagextension\flag\nm_SlingbagDummy_g.p3d";
		debug_ItemCategory=9;
		inventorySlot[]=
		{
			"Back"
		};
		attachments[]=
		{
			"WalkieTalkie"
		};
		itemInfo[]=
		{
			"Clothing",
			"Back"
		};
		rotationFlags=16;
		itemSize[]={4,4};
		itemsCargoSize[]={6,5};
		weight=900;
		varWetMax=1;
		heatIsolation=0.30000001;
		visibilityModifier=0.80000001;
		repairableWithKits[]={5,2};
		repairCosts[]={30,25};
		soundAttType="Small";
		hiddenSelections[]=
		{
			"camo"
		};
		class ClothingTypes
		{
			male="nm_Flagextension\flag\nm_SlingbagDummy_m.p3d";
			female="nm_Flagextension\flag\nm_SlingbagDummy_f.p3d";
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
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUpItem_Light
				{
					soundSet="pickUpCourierBag_Light_SoundSet";
					id=796;
				};
				class pickUpItem
				{
					soundSet="pickUpCourierBag_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="taloonbag_drop_SoundSet";
					id=898;
				};
			};
		};
	};
	class nm_ImproBagDummy: Clothing
	{
		scope=2;
		displayName="$STR_nmImproBag";
		descriptionShort="$STR_nmImproBagDISC";
		model="nm_Flagextension\flag\nm_ImproBagDummy_g.p3d";
		debug_ItemCategory=9;
		inventorySlot[]=
		{
			"Back"
		};
		attachments[]=
		{
			"Chemlight",
			"WalkieTalkie"
		};
		itemInfo[]=
		{
			"Clothing",
			"Back"
		};
		rotationFlags=16;
		itemSize[]={4,5};
		itemsCargoSize[]={7,6};
		weight=2400;
		varWetMax=1;
		heatIsolation=0.40000001;
		visibilityModifier=0.69999999;
		repairableWithKits[]={5,2};
		repairCosts[]={30,25};
		soundAttType="Small";
		hiddenSelections[]=
		{
			"camo"
		};
		class ClothingTypes
		{
			male="nm_Flagextension\flag\nm_ImproBagDummy_m.p3d";
			female="nm_Flagextension\flag\nm_ImproBagDummy_f.p3d";
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
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUpItem_Light
				{
					soundSet="pickUpCourierBag_Light_SoundSet";
					id=796;
				};
				class pickUpItem
				{
					soundSet="pickUpCourierBag_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="taloonbag_drop_SoundSet";
					id=898;
				};
			};
		};
	};
	class LongWoodenStick: Inventory_Base
	{
		scope=2;
		rotationFlags=1;
		model="nm_Flagextension\flag\nm_StickflagDummy.p3d";
		attachments[]+=
		{
			"Material_FPole_Flag"
		};
		hiddenSelections[]=
		{
			"posi_default",
			"posi_back",
			"stick",
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
	class nm_LongWoodenStick_deployed : Inventory_Base
	{
		scope = 2;
		displayName="$STR_CfgVehicles_LongWoodenStick0";
		descriptionShort="$STR_CfgVehicles_LongWoodenStick1";
		model="nm_Flagextension\flag\nm_StickflagDummy_deployed.p3d";
		overrideDrawArea="8.0";
		forceFarBubble="true";
		slopeTolerance=0.2;
		yawPitchRollLimit[]={45,45,45};
		carveNavmesh=1;
		canBeDigged=0;
		heavyItem=1;
		weight=10000;
		itemSize[]={2,2};
		repairableWithKits[]={};
		repairCosts[]={};
		itemBehaviour=0;
		absorbency=0.1;
		attachments[]+=
		{
			"Material_FPole_Flag"
		};
		hiddenSelections[]=
		{
			"posi_default",
			"stick",
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
	class nm_LongWoodenStick_Placing: nm_Flag_deployed
	{
		displayName="This is a hologram";
		descriptionShort="Nothing to see here, move along";
		model="nm_Flagextension\flag\nm_StickflagDummy_placing.p3d";
		attachments[]+=
		{
			"Material_FPole_Flag"
		};
		hiddenSelections[]=
		{
			"posi_default",
			"stick",
			"camo"
		};	
		alignHologramToTerain=0;
		slopeTolerance=0.30000001;
		storageCategory=10;
	};
	class CarScript;		///Note: To make custom cars compatible, just add the "Material_FPole_Flag" - Slot to theire config.No scripting needed as long as they inherit from CarScript
	class OffroadHatchback: CarScript
	{
		attachments[]+=
		{
			"Material_FPole_Flag"
		};
		class DamageSystem
		{
			class DamageZones
			{
				class Back
				{
					inventorySlots[]+=
					{
						"Material_FPole_Flag"
					};
				};
			};
		};
		class GUIInventoryAttachmentsProps
		{
			class Body
			{
				attachmentSlots[]+=
				{
					"Material_FPole_Flag"
				};
			};
		};		
	};
	class CivilianSedan: CarScript
	{
		attachments[]+=
		{
			"Material_FPole_Flag"
		};
		class DamageSystem
		{
			class DamageZones
			{
				class Back
				{
					inventorySlots[]+=
					{
						"Material_FPole_Flag"
					};
				};
			};
		};
		class GUIInventoryAttachmentsProps
		{
			class Body
			{
				attachmentSlots[]+=
				{
					"Material_FPole_Flag"
				};
			};
		};		
	};
	class Hatchback_02: CarScript
	{
		attachments[]+=
		{
			"Material_FPole_Flag"
		};
		class DamageSystem
		{
			class DamageZones
			{
				class Back
				{
					inventorySlots[]+=
					{
						"Material_FPole_Flag"
					};
				};
			};
		};
		class GUIInventoryAttachmentsProps
		{
			class Body
			{
				attachmentSlots[]+=
				{
					"Material_FPole_Flag"
				};
			};
		};		
	};
	class Sedan_02: CarScript
	{
		attachments[]+=
		{
			"Material_FPole_Flag"
		};
		class DamageSystem
		{
			class DamageZones
			{
				class Back
				{
					inventorySlots[]+=
					{
						"Material_FPole_Flag"
					};
				};
			};
		};
		class GUIInventoryAttachmentsProps
		{
			class Body
			{
				attachmentSlots[]+=
				{
					"Material_FPole_Flag"
				};
			};
		};		
	};
	class Truck_01_Base: CarScript
	{
		attachments[]+=
		{
			"Material_FPole_Flag"
		};
		class DamageSystem
		{
			class DamageZones
			{
				class Back
				{
					inventorySlots[]+=
					{
						"Material_FPole_Flag"
					};
				};
			};
		};
		class GUIInventoryAttachmentsProps
		{
			class Body
			{
				attachmentSlots[]+=
				{
					"Material_FPole_Flag"
				};
			};
		};		
	};
	class Offroad_02: CarScript
	{
		attachments[]+=
		{
			"Material_FPole_Flag"
		};
		class DamageSystem
		{
			class DamageZones
			{
				class Back
				{
					inventorySlots[]+=
					{
						"Material_FPole_Flag"
					};
				};
			};
		};
		class GUIInventoryAttachmentsProps
		{
			class Body
			{
				attachmentSlots[]+=
				{
					"Material_FPole_Flag"
				};
			};
		};		
	};
	class nm_CarflagDummy: Inventory_Base
	{
		scope=2;
		displayName="";
		model="nm_Flagextension\flag\nm_CarflagDummy.p3d";
		weight=10000;
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
						{1,{""}},
						{0.69999999,{""}},
						{0.5,{""}},
						{0.30000001,{""}},
						{0,{""}}
					};
				};
			};
		};
	};
};