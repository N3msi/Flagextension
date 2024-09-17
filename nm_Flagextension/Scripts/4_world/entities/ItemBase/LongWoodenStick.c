modded class LongWoodenStick
{
	private string m_nmFlagTexture; // Flag Texture
	private string m_nmStickTexture = "nm_Flagextension\\flag\\data\\nm_WoodenStick_co.paa"; // Tex Stick
	private string materialPathFlag; // stored flag mats on EEHealthLevelChanged
	private string materialPathStick; // stored stick mats on EEHealthLevelChanged
    private bool m_IsPosiDefault; // Save visible selection
    private bool m_IsPosiBack; // Save visible selection
	private bool m_IsNoFlag; // Save visible selection

	void LongWoodenStick()
    {   
		ApplyVisibility();
	}

	void ~LongWoodenStick()
    {
	}

	override void EEHealthLevelChanged(int oldLevel, int newLevel, string zone) 
    {
        super.EEHealthLevelChanged(oldLevel, newLevel, zone);

		switch (newLevel) //Sets Rvmats on Stick
		{
			case GameConstants.STATE_RUINED:
				materialPathStick = "nm_Flagextension\\flag\\data\\nm_WoodenStick_destruct.rvmat";
				break;
			case GameConstants.STATE_BADLY_DAMAGED:
			case GameConstants.STATE_DAMAGED:
				materialPathStick = "nm_Flagextension\\flag\\data\\nm_WoodenStick_damage.rvmat";
				break;
			case GameConstants.STATE_WORN:
			case GameConstants.STATE_PRISTINE:
				materialPathStick = "nm_Flagextension\\flag\\data\\nm_WoodenStick.rvmat";
				break;
			default:
				materialPathStick = "nm_Flagextension\\flag\\data\\nm_WoodenStick.rvmat"; // Fallback material
				break;
		}
        if (GetGame().IsServer())
        {
			Flag_Base attachedItem = Flag_Base.Cast(FindAttachmentBySlotName("Material_FPole_Flag"));
			if (attachedItem)
			{
				// Set same health to attached flag on dmg taken
				switch (newLevel)
				{
					case GameConstants.STATE_RUINED:
						attachedItem.SetHealthLevel(GameConstants.STATE_RUINED);		
						break;
					case GameConstants.STATE_BADLY_DAMAGED:
						attachedItem.SetHealthLevel(GameConstants.STATE_BADLY_DAMAGED);
						break;
					case GameConstants.STATE_DAMAGED:
						attachedItem.SetHealthLevel(GameConstants.STATE_DAMAGED);
						break;
					case GameConstants.STATE_WORN:
						attachedItem.SetHealthLevel(GameConstants.STATE_WORN);
						break;
					case GameConstants.STATE_PRISTINE:
						attachedItem.SetHealthLevel(GameConstants.STATE_PRISTINE);
						break;
				}
			}
        }
		DefineDummyMats();
		
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(ApplyTexture, 50, false, this);
    }
	
	void DefineDummyMats()
	{
		Flag_Base attachedItem = Flag_Base.Cast(FindAttachmentBySlotName("Material_FPole_Flag"));
		
		if (GetGame().IsServer() && attachedItem)
		{
			float health = attachedItem.GetHealth("", ""); 

			 //Sets Rvmats on flag
			if (health <= 0) 
			{
				materialPathFlag = "nm_Flagextension\\flag\\data\\nm_stickflag_destruct.rvmat";
			}
			else if (health > 0 && health < 50) 
			{
				materialPathFlag = "nm_Flagextension\\flag\\data\\nm_stickflag_damage.rvmat";
			}
			else if (health >= 50 && health <= 100) 
			{
				materialPathFlag = "nm_Flagextension\\flag\\data\\nm_stickflag.rvmat";
			}
			else
			{
				materialPathFlag = "nm_Flagextension\\flag\\data\\nm_stickflag.rvmat"; //default
			}
		}
		else
		{
			materialPathFlag = "nm_Flagextension\\flag\\data\\nm_stickflag.rvmat"; //default
		}
	}
	
    void Synchronize()
    {
        if (GetGame().IsServer())
        {
            SetSynchDirty();
        }
    }

    override void OnVariablesSynchronized()
    {
        super.OnVariablesSynchronized();
        ApplyVisibility();
    }

	void ApplyVisibility()
	{
		
		if (m_IsPosiDefault) // flag default visible
		{
			SetObjectTexture(0, m_nmFlagTexture);
			SetObjectMaterial(0, materialPathFlag);
			SetObjectTexture(1, "");
			SetObjectMaterial(1, "");
		}
		else if (m_IsPosiBack) // flag back visible
		{
			SetObjectTexture(1, m_nmFlagTexture);
			SetObjectMaterial(1, materialPathFlag);
			SetObjectTexture(0, "");
			SetObjectMaterial(0, "");
		}
		else if (m_IsNoFlag) // no flag visible
		{
			SetObjectTexture(0, ""); 
			SetObjectMaterial(0, ""); 
			SetObjectTexture(1, "");
			SetObjectMaterial(1, "");
		}
		// flag default visible
		else
		{
			SetObjectTexture(0, "");
			SetObjectMaterial(0, "");
			SetObjectTexture(1, "");
			SetObjectMaterial(1, "");
		}
		SetObjectTexture(2, m_nmStickTexture); 
		SetObjectMaterial(2, materialPathStick);
		
	}

    override void OnStoreSave(ParamsWriteContext ctx)
    {
        super.OnStoreSave(ctx);
        ctx.Write(m_nmFlagTexture); // Save Flag Tex
        ctx.Write(m_IsPosiDefault); // Save visible selection
        ctx.Write(m_IsPosiBack); // Save visible selection
        ctx.Write(m_IsNoFlag); // Save visible selection
    }

    override bool OnStoreLoad(ParamsReadContext ctx, int version)
    {
        if (!super.OnStoreLoad(ctx, version))
            return false;

        if (!ctx.Read(m_nmFlagTexture))
            return false;
		
        if (!ctx.Read(m_IsPosiDefault))
            m_IsPosiDefault = false;

        if (!ctx.Read(m_IsPosiBack))
            m_IsPosiBack = false;
		
        if (!ctx.Read(m_IsNoFlag))
            m_IsNoFlag = false;
		
        return true;
    }

	override void AfterStoreLoad()
	{	
        super.AfterStoreLoad();
		DefineDummyMats();
        ApplyVisibility();
	}

	void ApplyTexture(EntityAI parent)
	{
		if (GetGame().IsServer()) // serverside
		{
			PlayerBase player = null;
			if (parent)
			{
				EntityAI rootEntity = parent.GetHierarchyRootPlayer();
				if (rootEntity)
				{
					player = PlayerBase.Cast(rootEntity);
				}
			}

			Flag_Base attachedItem = Flag_Base.Cast(FindAttachmentBySlotName("Material_FPole_Flag"));
			
			if (attachedItem) // Flag is attached
			{
				if (player)
				{
					EntityAI meleeItem = player.FindAttachmentBySlotName("Melee");
					EntityAI shoulderItem = player.FindAttachmentBySlotName("Shoulder");

					if (meleeItem == this || shoulderItem == this) // flag back visible
					{
						m_IsPosiDefault = false;
						m_IsPosiBack = true;
						m_IsNoFlag = false;

						SetObjectTexture(0, ""); 
						SetObjectMaterial(0, ""); 
						SetObjectTexture(1, m_nmFlagTexture); 
						SetObjectMaterial(1, materialPathFlag);
					}
					else // flag default visible
					{
						m_IsPosiDefault = true;
						m_IsPosiBack = false;
						m_IsNoFlag = false;

						SetObjectTexture(0, m_nmFlagTexture); 
						SetObjectMaterial(0, materialPathFlag);
						SetObjectTexture(1, "");
						SetObjectMaterial(1, "");
					}
				}
				else // flag default visible
				{
					m_IsPosiDefault = true;
					m_IsPosiBack = false;
					m_IsNoFlag = false;

					SetObjectTexture(0, m_nmFlagTexture);
					SetObjectMaterial(0, materialPathFlag);
					SetObjectTexture(1, "");
					SetObjectMaterial(1, "");
				}
			}
			else // No flag visible
			{
				m_IsPosiDefault = false;
				m_IsPosiBack = false;
				m_IsNoFlag = true;

				SetObjectTexture(0, "");
				SetObjectMaterial(0, "");
				SetObjectTexture(1, "");
				SetObjectMaterial(1, "");
			}
			// stick always visible
			SetObjectTexture(2, m_nmStickTexture); 
			SetObjectMaterial(2, materialPathStick);
		}
	}

	override void OnWasAttached(EntityAI parent, int slot_id)
	{
		super.OnWasAttached(parent, slot_id);
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(ApplyTexture, 50, false, this);
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(Synchronize, 60, false);
	}

	override void OnWasDetached(EntityAI parent, int slot_id)
	{
		super.OnWasDetached(parent, slot_id);
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(ApplyTexture, 50, false, this);
	}

	override void EEItemAttached(EntityAI item, string slot_name)
	{
		super.EEItemAttached(item, slot_name);

		// check if Material_FPole_Flag
		if (slot_name == "Material_FPole_Flag")
		{
			Flag_Base attachedFlag = Flag_Base.Cast(item);
			if (attachedFlag)
			{		
				m_nmFlagTexture = attachedFlag.GetHiddenSelectionsTextures()[0]; // defines Mats for Dummy

				DefineDummyMats(); // defines Mats for Dummy
				
				GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(ApplyTexture, 50, false, this);
			}
		}
	}

	override void EEItemDetached(EntityAI item, string slot_name)
	{
		super.EEItemDetached(item, slot_name);

		// check if Material_FPole_Flag
		if (slot_name == "Material_FPole_Flag")
		{
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(ApplyTexture, 50, false, this);
		}
	}

	override bool CanReceiveAttachment( EntityAI attachment, int slotId )
	{
		if( !super.CanReceiveAttachment( attachment, slotId ) )
		{
			return false;
		}
		return !GetInventory().IsInCargo();
	}
	
	override bool CanPutInCargo( EntityAI parent )
    {
	   ItemBase attachedItem = ItemBase.Cast(FindAttachmentBySlotName("Material_FPole_Flag")); 
	   if(attachedItem)
		{
			return false;
		}
		return true;
    }
	
    override void SetActions()
    {
        super.SetActions();

        AddAction(ActionClapBearTrapWithThisItem);
        AddAction(ActionBreakLongWoodenStick);
        AddAction(ActionAttachToConstruction);
    }
};