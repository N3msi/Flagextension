modded class CarScript ///Note: To make custom cars compatible, just add the "Material_FPole_Flag" - Slot to theire config.No scripting needed as long as they inherit from CarScript
{
	private nm_CarflagDummy m_ItemDuplicate;

	void AddChildFlag()
	{
		if (GetGame().IsServer() && !GetGame().IsClient())
		{
			ItemBase attachedItem = ItemBase.Cast(FindAttachmentBySlotName("Material_FPole_Flag")); 
			
			if (attachedItem) // null check
			{
				m_ItemDuplicate = nm_CarflagDummy.Cast(GetGame().CreateObject("nm_CarflagDummy", vector.Zero));
				
				if (m_ItemDuplicate) 
				{
					m_ItemDuplicate.SetOrientation("0 0 0");
					m_ItemDuplicate.SetPosition("0 0 0");

					SetDuplicateProperties(m_ItemDuplicate, attachedItem);

					this.AddChild(m_ItemDuplicate, -1, false);
					m_ItemDuplicate.Update();

					m_ItemDuplicate.SetSynchDirty();
				}
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
	
	override void EEItemAttached(EntityAI item, string slot_name)	//seems to also get called on restart and so initiates the dummy again
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
	
	override void EEItemDetached(EntityAI item, string slot_name)
	{
		super.EEItemDetached(item, slot_name);

		// Check for Material_FPole_Flag slot
		if (slot_name == "Material_FPole_Flag")
		{
			DeleteDuplicatedItem();  // if flag delete duplicate
		}
	}

	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);
		
		if (GetGame().IsServer() && !GetGame().IsClient())
		{
			DeleteDuplicatedItem();
		}
	}

	override void OnBeforeTryDelete()
	{
		super.OnBeforeTryDelete();

		if (GetGame().IsServer() && !GetGame().IsClient())
		{
			DeleteDuplicatedItem();
		}
	}
	
	void DeleteDuplicatedItem()
	{
		if (GetGame().IsServer() && !GetGame().IsClient())
		{
			if (m_ItemDuplicate)
			{
				GetGame().ObjectDelete(m_ItemDuplicate);  // delete duplicate
				m_ItemDuplicate = null;  // clear ref
			}
		}
	}
	
	override void EEHealthLevelChanged(int oldLevel, int newLevel, string zone)
	{
		super.EEHealthLevelChanged(oldLevel,newLevel,zone);
		
		TransferHealthToDummy();
	}
	
	void TransferHealthToDummy()
	{
		if (GetGame().IsServer() && !GetGame().IsClient())
		{
			ItemBase attachedFlag = ItemBase.Cast(FindAttachmentBySlotName("Material_FPole_Flag")); 
			
			if (attachedFlag && m_ItemDuplicate)
			{
				float carHealth = GetHealth("", ""); 

				if (carHealth <= 0)  // if car is ruined
				{
					attachedFlag.SetHealth("", "", 0);  // ruin flag					
					m_ItemDuplicate.SetHealth("", "", 0);  // ruin duplicate
				}
			}
		}
	}
}