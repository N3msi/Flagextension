modded class LongWoodenStick
{
	private Object m_ItemDuplicate;
	private vector nmDefaultPosition = "0 0 0"; // default position
	private vector nmDefaultOrientation = "0 0 0"; // default orientation
	private vector nmBackPosition = "0 0.3 0"; // position on back
	private vector nmBackOrientation = "40 180 0"; // position on back

	void LongWoodenStick()
    {   
		AddChildFlag(); // recreate AddChild if flag is available each restart/relog
	}

	void ~LongWoodenStick()
    {
		DeleteDuplicatedItem()
	}

	override void AfterStoreLoad()
	{	
        super.AfterStoreLoad();
	}

   override void EEItemAttached(EntityAI item, string slot_name)
    {
        super.EEItemAttached(item, slot_name);

		if (GetGame().IsServer() && !GetGame().IsClient())
		{
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(AddChildFlag, 100, false);
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

			nm_StickflagDummy FlagBaseDuplicate = nm_StickflagDummy.Cast(m_ItemDuplicate);
			if (FlagBaseDuplicate)
			{
				SetDuplicateProperties(FlagBaseDuplicate, attachedFlag);

				this.AddChild(m_ItemDuplicate, -1, false);
				m_ItemDuplicate.Update();
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

		if (GetGame().IsServer() && !GetGame().IsClient())
		{
			if (m_ItemDuplicate)
			{
			m_ItemDuplicate.SetPosition(nmBackPosition);
			m_ItemDuplicate.SetOrientation(nmBackOrientation);
			}
		}
	}

	override void OnWasDetached(EntityAI parent, int slot_id)
	{
		super.OnWasDetached(parent, slot_id);
		
		if (GetGame().IsServer() && !GetGame().IsClient())
		{
			if (m_ItemDuplicate)
			{
				// reset position orientation
				m_ItemDuplicate.SetPosition(nmDefaultPosition);
				m_ItemDuplicate.SetOrientation(nmDefaultOrientation);
			}
		}
	}

	override void EEItemDetached(EntityAI item, string slot_name)
    {
        super.EEItemDetached(item, slot_name);

		DeleteDuplicatedItem()
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
		super.EEHealthLevelChanged(oldLevel, newLevel, zone);

		// Calculate health percentage
		float maxHealth = GetMaxHealth("", "");
		float currentHealth = GetHealth("", "");
		float healthPercentage = (currentHealth / maxHealth) * 100;

		// Update the health of the duplicated item if it exists
		if (m_ItemDuplicate)
		{
			nm_StickflagDummy FlagBaseDuplicate = nm_StickflagDummy.Cast(m_ItemDuplicate);
			if (FlagBaseDuplicate)
			{
				// Set the duplicated item's health based on the percentage
				FlagBaseDuplicate.SetHealth("", "", maxHealth * (healthPercentage / 100));
			}
		}

		// Update the health of the attached flag
		Flag_Base attachedFlag = Flag_Base.Cast(FindAttachmentBySlotName("Material_FPole_Flag"));
		if (attachedFlag)
		{
			attachedFlag.SetHealth("", "", maxHealth * (healthPercentage / 100));
		}
	}
	
    override void SetActions()
    {
        super.SetActions();

        AddAction(ActionClapBearTrapWithThisItem);
        AddAction(ActionBreakLongWoodenStick);
        AddAction(ActionAttachToConstruction);
    }
};