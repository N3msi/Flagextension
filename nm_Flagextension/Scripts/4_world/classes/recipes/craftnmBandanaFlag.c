class nm_CraftBandanaFlag extends RecipeBase
{	
	override void Init()
	{
		m_Name = "#STR_craftnmBandana";
		m_IsInstaRecipe = false;//should this recipe be performed instantly without animation
		m_AnimationLength = 1.8;//animation length in relative time units
		m_Specialty = 0.01;// value > 0 for roughness, value < 0 for precision

		//conditions
		m_MinDamageIngredient[0] = -1;
		m_MaxDamageIngredient[0] = 3;
		m_MinQuantityIngredient[0] = -1;
		m_MaxQuantityIngredient[0] = -1;
		
		m_MinDamageIngredient[1] = -1;
		m_MaxDamageIngredient[1] = 3;
		m_MinQuantityIngredient[1] = -1;
		m_MaxQuantityIngredient[1] = -1;
		
		
		//ingredient 1
		InsertIngredient(0,"Flag_Base");//you can insert multiple ingredients this way
		InsertIngredient(0,"nm_ArmbandDummy");//you can insert multiple ingredients this way
		
		m_IngredientAddHealth[0] = 0;
		m_IngredientSetHealth[0] = -1; // -1 = do nothing
		m_IngredientAddQuantity[0] = 0;
		m_IngredientDestroy[0] = 1;
		m_IngredientUseSoftSkills[1] = false;// set 'true' to allow modification of the values by softskills on this ingredient
		
		//ingredient 2
		InsertIngredient(1,"Sickle");//you can insert multiple ingredients this way
		InsertIngredient(1,"KukriKnife");
		InsertIngredient(1,"FangeKnife");
		InsertIngredient(1,"Hacksaw");
		InsertIngredient(1,"HandSaw");
		InsertIngredient(1,"KitchenKnife");
		InsertIngredient(1,"SteakKnife");
		InsertIngredient(1,"HayHook");
		InsertIngredient(1,"StoneKnife");
		InsertIngredient(1,"Cleaver");
		InsertIngredient(1,"CombatKnife");
		InsertIngredient(1,"HuntingKnife");
		InsertIngredient(1,"Machete");
		InsertIngredient(1,"CrudeMachete");
		InsertIngredient(1,"OrientalMachete");
		InsertIngredient(1,"Screwdriver");
		InsertIngredient(1,"Crowbar");
		InsertIngredient(1,"Pickaxe");
		InsertIngredient(1,"WoodAxe");
		InsertIngredient(1,"Hatchet");
		InsertIngredient(1,"FirefighterAxe");
		InsertIngredient(1,"Sword");
		InsertIngredient(1,"AK_Bayonet");
		InsertIngredient(1,"M9A1_Bayonet");
		InsertIngredient(1,"Mosin_Bayonet");
		InsertIngredient(1,"SKS_Bayonet");
		InsertIngredient(1,"BoneKnife");
		
		m_IngredientAddHealth[1] = -5;
		m_IngredientSetHealth[1] = -1; // -1 = do nothing
		m_IngredientAddQuantity[1] = 0;
		m_IngredientDestroy[1] = 0;
		m_IngredientUseSoftSkills[1] = true;// set 'true' to allow modification of the values by softskills on this ingredient
		
		// crafting multiple results
		//result1
		AddResult("nm_BandanaDummy");
		m_ResultSetFullQuantity[0] = false;
		m_ResultSetQuantity[0] = -1;
		m_ResultSetHealth[0] = -1;
		m_ResultInheritsHealth[0] = 0;// (value) == -1 means do nothing; a (value) >= 0 means this result will inherit health from ingredient number (value);(value) == -2 means this result will inherit health from all ingredients averaged(result_health = combined_health_of_ingredients / number_of_ingredients)
		m_ResultInheritsColor[0] = -1;// (value) == -1 means do nothing; a (value) >= 0 means this result classname will be a composite of the name provided in AddResult method and config value "color" of ingredient (value)
		m_ResultToInventory[0] = -2;
		m_ResultUseSoftSkills[0] = true;// set 'true' to allow modification of the values by softskills on this result
		m_ResultReplacesIngredient[0] = -1;// value == -1 means do nothing; a value >= 0 means this result will transfer item propertiesvariables, attachments etc.. from an ingredient value
		
		//result2
		AddResult("nm_BandanaDummy");//single result
		m_ResultSetFullQuantity[1] = false;
		m_ResultSetQuantity[1] = -1;
		m_ResultSetHealth[1] = -1;
		m_ResultInheritsHealth[1] = 0;// (value) == -1 means do nothing; a (value) >= 0 means this result will inherit health from ingredient number (value);(value) == -2 means this result will inherit health from all ingredients averaged(result_health = combined_health_of_ingredients / number_of_ingredients)
		m_ResultInheritsColor[1] = -1;// (value) == -1 means do nothing; a (value) >= 0 means this result classname will be a composite of the name provided in AddResult method and config value "color" of ingredient (value)
		m_ResultToInventory[1] = -2;
		m_ResultUseSoftSkills[1] = true;// set 'true' to allow modification of the values by softskills on this result
		m_ResultReplacesIngredient[1] = -1;// value == -1 means do nothing; a value >= 0 means this result will transfer item propertiesvariables, attachments etc.. from an ingredient value
		
		//result3
		AddResult("nm_BandanaDummy");//single result
		m_ResultSetFullQuantity[2] = false;
		m_ResultSetQuantity[2] = -1;
		m_ResultSetHealth[2] = -1;
		m_ResultInheritsHealth[2] = 0;// (value) == -1 means do nothing; a (value) >= 0 means this result will inherit health from ingredient number (value);(value) == -2 means this result will inherit health from all ingredients averaged(result_health = combined_health_of_ingredients / number_of_ingredients)
		m_ResultInheritsColor[2] = -1;// (value) == -1 means do nothing; a (value) >= 0 means this result classname will be a composite of the name provided in AddResult method and config value "color" of ingredient (value)
		m_ResultToInventory[2] = -2;
		m_ResultUseSoftSkills[2] = true;// set 'true' to allow modification of the values by softskills on this result
		m_ResultReplacesIngredient[2] = -1;// value == -1 means do nothing; a value >= 0 means this result will transfer item propertiesvariables, attachments etc.. from an ingredient value

	}

	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return ingredients[0].IsEmpty();
	}

	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)
	{
		ItemBase ingredient0 = ingredients[0];
		string nmFlagTexture = "";

		if (ingredient0.IsInherited(Flag_Base))
		{
			// if Flag_Base get tex from index0
			nmFlagTexture = ingredient0.GetHiddenSelectionsTextures()[0]; 
		}
		else if (ingredient0.IsInherited(nm_ArmbandDummy))
		{
			// if nm_ArmbandDummy get tex from GetnmFlagTexture
			nm_ArmbandDummy armbandDummy = nm_ArmbandDummy.Cast(ingredient0);
			if (armbandDummy)
			{
				nmFlagTexture = armbandDummy.GetnmFlagTexture();
			}
		}

		// transfer nmFlagTexture to armbands
		for (int i = 0; i < results.Count(); i++)
		{
			ItemBase bandana = results[i];
			bandana.SetObjectTexture(2, nmFlagTexture);
			nm_BandanaDummy bandanaDummyResult = nm_BandanaDummy.Cast(bandana);
			if (bandanaDummyResult)
			{
				bandanaDummyResult.SetnmFlagTexture(nmFlagTexture);
			}
		}
	}
};