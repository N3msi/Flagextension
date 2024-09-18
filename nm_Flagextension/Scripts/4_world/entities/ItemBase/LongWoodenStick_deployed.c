class nm_LongWoodenStick_deployed extends ItemBase
{
	private string m_nmFlagTexture; // Flag Texture
	private string m_nmStickTexture = "nm_Flagextension\\flag\\data\\nm_WoodenStick_co.paa"; // Tex Stick
	private string materialPathFlag; // stored flag mats on EEHealthLevelChanged
	private string materialPathStick; // stored stick mats on EEHealthLevelChanged
    private bool m_IsFlag; // Save visible selection
	private bool m_IsNoFlag; // Save visible selection

	void nm_LongWoodenStick_deployed()
    {   
		ApplyVisibility();
	}

	void ~nm_LongWoodenStick_deployed()
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
			ItemBase attachedItem = ItemBase.Cast(FindAttachmentBySlotName("Material_FPole_Flag"));
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
		ItemBase attachedItem = ItemBase.Cast(FindAttachmentBySlotName("Material_FPole_Flag"));
		
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
		if (m_IsFlag) // flag default visible
		{
			SetObjectTexture(0, m_nmFlagTexture);
			SetObjectMaterial(0, materialPathFlag);
		}
		else if (m_IsNoFlag) // no flag visible
		{
			SetObjectTexture(0, ""); 
			SetObjectMaterial(0, ""); 
		}
		// flag default visible
		else
		{
			SetObjectTexture(0, "");
			SetObjectMaterial(0, "");
		}
		SetObjectTexture(1, m_nmStickTexture); 
		SetObjectMaterial(1, materialPathStick);	
	}

    override void OnStoreSave(ParamsWriteContext ctx)
    {
        super.OnStoreSave(ctx);
        ctx.Write(m_nmFlagTexture); // Save Flag Tex
        ctx.Write(m_IsFlag); // Save visible selection
        ctx.Write(m_IsNoFlag); // Save visible selection
    }

    override bool OnStoreLoad(ParamsReadContext ctx, int version)
    {
        if (!super.OnStoreLoad(ctx, version))
            return false;

        if (!ctx.Read(m_nmFlagTexture))
            return false;
		
        if (!ctx.Read(m_IsFlag))
            m_IsFlag = false;
		
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
			ItemBase attachedItem = ItemBase.Cast(FindAttachmentBySlotName("Material_FPole_Flag"));
			
			if (attachedItem) // Flag is attached
			{
				m_IsFlag = true;
				m_IsNoFlag = false;

				SetObjectTexture(0, m_nmFlagTexture); 
				SetObjectMaterial(0, materialPathFlag);
			}
			else // No flag attached
			{
				m_IsFlag = false;
				m_IsNoFlag = true;

				SetObjectTexture(0, "");
				SetObjectMaterial(0, "");
			}
			// stick always visible
			SetObjectTexture(1, m_nmStickTexture); 
			SetObjectMaterial(1, materialPathStick);
		}
	}
	
	override void EEItemAttached(EntityAI item, string slot_name)
	{
		super.EEItemAttached(item, slot_name);

		// check if Material_FPole_Flag
		if (slot_name == "Material_FPole_Flag")
		{
			ItemBase attachedFlag = ItemBase.Cast(item);
			
			if (attachedFlag)
			{
				// check if  nm_ArmbandDummy
				nm_ArmbandDummy armbandDummy = nm_ArmbandDummy.Cast(attachedFlag);
				
				
				if (!armbandDummy) // if not nm_ArmbandDummy GetHiddenSelectionsTextures
				{
					m_nmFlagTexture = attachedFlag.GetHiddenSelectionsTextures()[0];
				}
				else // if not nm_ArmbandDummy GetnmFlagTexture
				{
					m_nmFlagTexture = armbandDummy.GetnmFlagTexture();
				}

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

	override bool CanPutInCargo( EntityAI parent )
    {
        return false;
    }
    
    override bool CanPutIntoHands(EntityAI parent)
    {
        return false;
    }
	
};

class nm_LongWoodenStick_placing extends ItemBase
{

	protected void nm_LongWoodenStick_placing()
	{
		SetIsHologram(true);
	}
	
	override bool IsDeployable()
	{
		return false;
	}

	override void OnItemLocationChanged(EntityAI old_owner, EntityAI new_owner)
	{
        super.OnItemLocationChanged(old_owner, new_owner);

        // Delete the item whenever its location changes
        GetGame().ObjectDelete(this);
	}
}