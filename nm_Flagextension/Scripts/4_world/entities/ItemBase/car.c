modded class CarScript ///Note: To make custom cars compatible, just add the "Material_FPole_Flag" - Slot to theire config.No scripting needed as long as they inherit from CarScript
{
	private nm_CarflagDummy m_ItemDuplicate;

    override void OnStoreSave(ParamsWriteContext ctx)
    {
        super.OnStoreSave(ctx);
        ctx.Write(m_ItemDuplicate); // Save nm_CarflagDummy
    }

    override bool OnStoreLoad(ParamsReadContext ctx, int version)
    {
        if (!super.OnStoreLoad(ctx, version))
            return false;

        if (!ctx.Read(m_ItemDuplicate))
            return false;
				
        return true;
    }

    override void AfterStoreLoad()
    {
		super.AfterStoreLoad();
		
		DeleteOldFlag();
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(AddChildFlag, 10, false);
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
	
	void DeleteOldFlag() // To delete unattached Dummy after restart, otherwise floating in air
	{
		float radius = 1.0;

		vector carPosition = GetPosition();

		array<Object> objectsInRange = new array<Object>;

		GetGame().GetObjectsAtPosition(carPosition, radius, objectsInRange, null);

		foreach (Object obj : objectsInRange)
		{
			if (obj.IsInherited(nm_CarflagDummy))
			{
				GetGame().ObjectDelete(obj);
			}
		}
	}
	
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
		DeleteOldFlag();
	}

	override void EEHealthLevelChanged(int oldLevel, int newLevel, string zone)
	{
		super.EEHealthLevelChanged(oldLevel, newLevel, zone);

		// Calculate health percentage
		float maxHealth = GetMaxHealth("", "");
		float currentHealth = GetHealth("", "");
		float healthPercentage = (currentHealth / maxHealth) * 100;

		// Update health of duplicate
		if (m_ItemDuplicate)
		{
			nm_CarflagDummy itemBaseDuplicate = nm_CarflagDummy.Cast(m_ItemDuplicate);
			if (itemBaseDuplicate)
			{
				// set duplicate health
				itemBaseDuplicate.SetHealth("", "", maxHealth * (healthPercentage / 100));
			}
		}

		// update health attached flag
		ItemBase attachedFlag = ItemBase.Cast(FindAttachmentBySlotName("Material_FPole_Flag"));
		if (attachedFlag)
		{
			attachedFlag.SetHealth("", "", maxHealth * (healthPercentage / 100));
		}
	}
}