modded class LongWoodenStick
{
	private nm_StickflagDummy m_ItemDuplicate;
	private vector nmDefaultPosition = "0 0 0"; // default position
	private vector nmDefaultOrientation = "0 0 0"; // default orientation
	private vector nmBackPosition = "0 0.3 0"; // position on back
	private vector nmBackOrientation = "40 180 0"; // position on back
	
	void LongWoodenStick()
    {   
	}

	void ~LongWoodenStick()
    {
	}

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
		
		DeleteOldFlag()		
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(AddChildFlag, 10, false);
    }
	
    override void SetActions()
    {
        super.SetActions();
        
        AddAction(ActionClapBearTrapWithThisItem);
        AddAction(ActionBreakLongWoodenStick);
        AddAction(ActionAttachToConstruction);
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
		float radius = 0.5;

		vector carPosition = GetPosition();

		array<Object> objectsInRange = new array<Object>;

		GetGame().GetObjectsAtPosition(carPosition, radius, objectsInRange, null);

		foreach (Object obj : objectsInRange)
		{
			if (obj.IsInherited(nm_StickflagDummy))
			{
				GetGame().ObjectDelete(obj);
			}
		}
	}
	
	void AddChildFlag()
	{
		if (GetGame().IsServer() && !GetGame().IsClient())
		{
			Flag_Base attachedFlag = Flag_Base.Cast(FindAttachmentBySlotName("Material_FPole_Flag"));

			if (!attachedFlag) return; // check valid attachedFlag

			m_ItemDuplicate = GetGame().CreateObject("nm_StickflagDummy", vector.Zero);

			PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());

			if (attachedFlag) // null check
			{
				if (player)
				{
					EntityAI slot1Item = player.FindAttachmentBySlotName("Melee");
					EntityAI slot2Item = player.FindAttachmentBySlotName("Shoulder");
					if (slot1Item == this || slot2Item == this)
					{
						// stick is in melee or shoulder slot
						m_ItemDuplicate.SetPosition(nmBackPosition);
						m_ItemDuplicate.SetOrientation(nmBackOrientation);
					}	
					else 
					{ // stick isnt in melee or shoulder slot
						m_ItemDuplicate.SetPosition(nmDefaultPosition);
						m_ItemDuplicate.SetOrientation(nmDefaultOrientation);
					}
				} // stick is not in player
				else
				{
					m_ItemDuplicate.SetPosition(nmDefaultPosition);
					m_ItemDuplicate.SetOrientation(nmDefaultOrientation);
				}
			}
			
			nm_StickflagDummy FlagBaseDuplicate = nm_StickflagDummy.Cast(m_ItemDuplicate);
			if (FlagBaseDuplicate)
			{
				SetDuplicateProperties(FlagBaseDuplicate, attachedFlag);

				this.AddChild(m_ItemDuplicate, -1, false);
				m_ItemDuplicate.Update();
				m_ItemDuplicate.SetSynchDirty();
			}
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
	
	override void OnWasAttached(EntityAI parent, int slot_id)
	{
		super.OnWasAttached(parent, slot_id);
		
		if (m_ItemDuplicate)
		{

			m_ItemDuplicate.SetPosition(nmBackPosition);
			m_ItemDuplicate.SetOrientation(nmBackOrientation);
		}
	}
	
	override void OnWasDetached(EntityAI parent, int slot_id)
	{
		super.OnWasDetached(parent, slot_id);
		
		if (m_ItemDuplicate)
		{
			// reset position orientation
			m_ItemDuplicate.SetPosition(nmDefaultPosition);
			m_ItemDuplicate.SetOrientation(nmDefaultOrientation);
		}
	}
	
	override void EEItemDetached(EntityAI item, string slot_name)
    {
		super.EEItemDetached(item, slot_name);

		DeleteOldFlag()
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

		// calculate health percentage
		float maxHealth = GetMaxHealth("", "");
		float currentHealth = GetHealth("", "");
		float healthPercentage = (currentHealth / maxHealth) * 100;

		// Update health of duplicate
		if (m_ItemDuplicate)
		{
			nm_StickflagDummy FlagBaseDuplicate = nm_StickflagDummy.Cast(m_ItemDuplicate);
			if (FlagBaseDuplicate)
			{
				// Set duplicate health
				FlagBaseDuplicate.SetHealth("", "", maxHealth * (healthPercentage / 100));
			}
		}

		// Update health attached flag
		Flag_Base attachedFlag = Flag_Base.Cast(FindAttachmentBySlotName("Material_FPole_Flag"));
		if (attachedFlag)
		{
			attachedFlag.SetHealth("", "", maxHealth * (healthPercentage / 100));
		}
	}
};