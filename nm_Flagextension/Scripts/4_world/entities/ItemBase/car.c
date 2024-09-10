modded class CarScript
{
	private nm_CarflagDummy m_ItemDuplicate;
	
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
			if (slot_name == "Material_FPole_Flag" && Flag_Base.Cast(item))
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
			
			m_ItemDuplicate = nm_CarflagDummy.Cast(GetGame().CreateObject("nm_CarflagDummy", vector.Zero));
			
			if (m_ItemDuplicate) 
			{
				m_ItemDuplicate.SetOrientation("0 0 0");
				m_ItemDuplicate.SetPosition("0 0 0");

				if (attachedItem)
				{
					SetDuplicateProperties(m_ItemDuplicate, ItemBase.Cast(attachedItem));
				}

				this.AddChild(m_ItemDuplicate, -1, false);
				m_ItemDuplicate.Update();
			}
		}
	}
		
    void SetDuplicateProperties(nm_CarflagDummy itemBaseDuplicate, ItemBase attachedFlag)
    {
		if (itemBaseDuplicate)
		{
			string nmFlagTexture = "";
			nmFlagTexture = attachedFlag.GetHiddenSelectionsTextures()[0];
			
			itemBaseDuplicate.SetnmFlagTexture(nmFlagTexture);
			
			float attachedFlagHealth = attachedFlag.GetHealth("", ""); // get health
			itemBaseDuplicate.SetHealth("", "", attachedFlagHealth); // set health
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
			nm_CarflagDummy itemBaseDuplicate = nm_CarflagDummy.Cast(m_ItemDuplicate);
			if (itemBaseDuplicate)
			{
				// set duplicated items health based (percentage)
				itemBaseDuplicate.SetHealth("", "", maxHealth * (healthPercentage / 100));
			}
		}

		// update health of attached flag (percentage)
		ItemBase attachedFlag = ItemBase.Cast(FindAttachmentBySlotName("Material_FPole_Flag"));
		if (attachedFlag)
		{
			attachedFlag.SetHealth("", "", maxHealth * (healthPercentage / 100));
		}
	}
};