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

	void AddChildFlag()
	{
		if (GetGame().IsServer() && !GetGame().IsClient())
		{
			if (m_ItemDuplicate)
			{
				return;
			}
		
			Flag_Base attachedItem = Flag_Base.Cast(FindAttachmentBySlotName("Material_FPole_Flag"));

			if (attachedItem) // null check
			{
				m_ItemDuplicate = nm_StickflagDummy.Cast(GetGame().CreateObject("nm_StickflagDummy", vector.Zero));

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

				if (m_ItemDuplicate)
				{
					SetDuplicateProperties(m_ItemDuplicate, attachedItem);
					m_ItemDuplicate.SetParent(this);

					this.AddChild(m_ItemDuplicate, -1, false);
					m_ItemDuplicate.Update();
				}
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

   override void EEItemAttached(EntityAI item, string slot_name)	//seems to also get called on restart and so initiates the dummy again
    {
        super.EEItemAttached(item, slot_name);

		if (GetGame().IsServer() && !GetGame().IsClient())
		{
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(AddChildFlag, 100, false);
		}
	}

	override void EEItemLocationChanged(notnull InventoryLocation oldLoc, notnull InventoryLocation newLoc)
	{
		super.EEItemLocationChanged(oldLoc, newLoc);

		bool isValidLocation = false;

		// check if new location is hands, ground or attached
		if (newLoc.GetType() == InventoryLocationType.HANDS || newLoc.GetType() == InventoryLocationType.GROUND || newLoc.GetType() == InventoryLocationType.ATTACHMENT )
		{
			isValidLocation = true;
		}

		// delete dummy if not valid location ( = is in inventory )
		if (!isValidLocation)
		{
			DeleteDuplicatedItem(); 
		}
		else
		{
			AddChildFlag(); // try recreate dummy
		}
	}

	override void OnWasAttached(EntityAI parent, int slot_id)
	{
		super.OnWasAttached(parent, slot_id);
		
		if (GetGame().IsServer() && !GetGame().IsClient())
		{
			if (m_ItemDuplicate)
			{
			// change posi & ori to fit backslot
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

		DeleteDuplicatedItem();
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

    override void OnBeforeTryDelete()
    {
        super.OnBeforeTryDelete();
        
        if (GetGame().IsServer() && !GetGame().IsClient())
        {
            DeleteDuplicatedItem();  // clean dummy before deleted
        }
    }
	
	override void EEHealthLevelChanged(int oldLevel, int newLevel, string zone)
	{
		super.EEHealthLevelChanged(oldLevel, newLevel, zone);
		
		if (GetGame().IsServer() && !GetGame().IsClient())
		{
			// check if parent is ruined
			if (newLevel == GameConstants.STATE_RUINED)
			{
				// find & ruin flag
				Flag_Base attachedFlag = Flag_Base.Cast(FindAttachmentBySlotName("Material_FPole_Flag"));

				if (attachedFlag)
				{
					attachedFlag.SetHealth("", "", 0);
				}

				// find & ruin dummy
				if (m_ItemDuplicate)
				{
					nm_StickflagDummy flagDummy = nm_StickflagDummy.Cast(m_ItemDuplicate);
					if (flagDummy)
					{
						flagDummy.SetHealth("", "", 0);
					}
				}
			}
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