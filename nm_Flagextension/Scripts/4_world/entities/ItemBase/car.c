modded class CarScript
{
	private Object m_ItemDuplicate;
	
	void CarScript()
    {   
	}

	void ~CarScript()
    {
	}
	
	override void EEItemAttached(EntityAI item, string slot_name)
	{
		super.EEItemAttached(item, slot_name);

		if (GetGame().IsServer() && !GetGame().IsClient())
		{
			// Check for Material_FPole_Flag slot
			if (slot_name == "Material_FPole_Flag")
			{
				GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(AddChildFlag, 10, false);
			}
		}
	}

	void AddChildFlag()
	{
		if (GetGame().IsServer() && !GetGame().IsClient())
		{
			ItemBase attachedItem = ItemBase.Cast(FindAttachmentBySlotName("Material_FPole_Flag")); 
			
			m_ItemDuplicate = GetGame().CreateObject("nm_CarflagDummy", vector.Zero);
			
			m_ItemDuplicate.SetOrientation("0 0 0");
			m_ItemDuplicate.SetPosition("0 0 0");

			ItemBase itemBaseDuplicate = ItemBase.Cast(m_ItemDuplicate);
			if (itemBaseDuplicate && attachedItem)
			{
				SetDuplicateProperties(itemBaseDuplicate, attachedItem);
			}

			this.AddChild(m_ItemDuplicate, -1, false);
			m_ItemDuplicate.Update();
		}
	}
		
    void SetDuplicateProperties(nm_StickflagDummy FlagBaseDuplicate, Flag_Base attachedFlag)
    {
		if (FlagBaseDuplicate)
		{
			string nmFlagTexture = "";
			nmFlagTexture = attachedFlag.GetHiddenSelectionsTextures()[0];
			
			FlagBaseDuplicate.SetnmFlagTexture(nmFlagTexture);
			
			float attachedFlagHealth = attachedFlag.GetHealth("", ""); // get health
			FlagBaseDuplicate.SetHealth("", "", attachedFlagHealth); // set health
		}
    }
	
	override void EEItemDetached(EntityAI item, string slot_name)
	{
		super.EEItemDetached(item, slot_name);

		// Check for Material_FPole_Flag slot
		if (slot_name == "Material_FPole_Flag")
		{
			DeleteDuplicatedItem();  // if flag delete duplicate
		}
	}

	void DeleteDuplicatedItem()
	{
		if (m_ItemDuplicate)
		{
			GetGame().ObjectDelete(m_ItemDuplicate);  // delete duplicate
			m_ItemDuplicate = null;  // clear ref
		}
	}

	override void EEHealthLevelChanged(int oldLevel, int newLevel, string zone)
	{
		super.EEHealthLevelChanged(oldLevel, newLevel, zone);

		// Calculate health percentage
		float maxHealth = GetMaxHealth("", "");
		float currentHealth = GetHealth("", "");
		float healthPercentage = (currentHealth / maxHealth) * 100;

		// Update health of duplicated item if it exists
		if (m_ItemDuplicate)
		{
			nm_StickflagDummy FlagBaseDuplicate = nm_StickflagDummy.Cast(m_ItemDuplicate);
			if (FlagBaseDuplicate)
			{
				// set duplicated items health based (percentage)
				FlagBaseDuplicate.SetHealth("", "", maxHealth * (healthPercentage / 100));
			}
		}

		// update health of attached flag (percentage)
		Flag_Base attachedFlag = Flag_Base.Cast(FindAttachmentBySlotName("Material_FPole_Flag"));
		if (attachedFlag)
		{
			attachedFlag.SetHealth("", "", maxHealth * (healthPercentage / 100));
		}
	}
};