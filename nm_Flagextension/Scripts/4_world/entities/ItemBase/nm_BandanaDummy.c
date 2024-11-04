class nm_BandanaDummy: Clothing
{
    private string m_nmFlagTexture; // Flag Texture
    private string m_nmFlagName; // Flag Name
	private string materialPath; // stored mats on EEHealthLevelChanged
    private int m_lastAttachedSlot; // attachement slot
    private bool m_IsMaskVisible; // store last shown selection
    private bool m_IsHeadgearVisible; // store last shown selection
	

	
	void nm_BandanaDummy()
	{
		SetObjectTexture(2, m_nmFlagTexture); // Apply tex on _g permanently
		SetObjectMaterial(2, materialPath); // show mats on _g ( better safe then sorry )
		ApplyVisibility();
	}

	void ~nm_BandanaDummy()
    {	
	}

	override bool CanHaveWetness()
	{
		return false;
	}
	
	override bool CanBeDisinfected()
	{
		return true;
	}
	
	override float GetBandagingEffectivity()
	{
		return 0.5;
	};
	
	override float GetInfectionChance(int system = 0, Param param = null)
	{
		if(m_Cleanness == 1)
		{
			return 0.00;
		}
		else
		{
			return 0.15;
		}
	}
	
	override protected set<int> GetAttachmentExclusionInitSlotValue(int slotId)
	{
		set<int> ret = super.GetAttachmentExclusionInitSlotValue(slotId);
		switch (slotId)
		{
			case InventorySlots.HEADGEAR:
				return ret;//no discernable conflict here
			break;
			
			default:
				ret.Insert(EAttExclusions.EXCLUSION_MASK_3);
				
				ret.Insert(EAttExclusions.SHAVING_MASK_ATT_0);
			break;
		}
		return ret;
	}

	void SetFlagAttributes(string texturePath, string nmFlagName)
    {
        m_nmFlagTexture = texturePath;
        m_nmFlagName = nmFlagName;
    }

    void SetnmFlagName(string name) // sets flagname from attaching Flag
    {
        m_nmFlagName = name;
    }
	
    string GetnmFlagName()
    {
        return m_nmFlagName;
    }
	
	string GetnmFlagTexture()
    {
        return m_nmFlagTexture;
    }
	
    void SetnmFlagTexture(string texturePath) // sets tex from attaching Flag
    {
        m_nmFlagTexture = texturePath;
    }
	
	void Synchronize()
	{
		if ( GetGame().IsServer() )
		{
			SetSynchDirty();
		}
	}
	
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		ApplyVisibility();	
	}
	
	override void EEHealthLevelChanged(int oldLevel, int newLevel, string zone) 	///bypassing damagesys to apply Material
    {
        super.EEHealthLevelChanged(oldLevel, newLevel, zone);

        switch (newLevel)
        {
            case GameConstants.STATE_RUINED:
                materialPath = "nm_Flagextension\\flag\\data\\nm_Bandana_destruct.rvmat"; // Mat ruined
                break;
            case GameConstants.STATE_BADLY_DAMAGED:
            case GameConstants.STATE_DAMAGED:
                materialPath = "nm_Flagextension\\flag\\data\\nm_Bandana_damage.rvmat"; // Mat badly damaged/damaged
                break;
            case GameConstants.STATE_WORN:
            case GameConstants.STATE_PRISTINE:
                materialPath = "nm_Flagextension\\flag\\data\\nm_Bandana.rvmat"; // Mat worn/pristine
                break;
            default:
                materialPath = "nm_Flagextension\\flag\\data\\nm_Bandana.rvmat"; // Fallback material
                break;
        }

        // Reapply visibility and material
        ApplyVisibility();
    }
	
	void ApplyVisibility()
    {
        if (m_IsMaskVisible)
		{
			SetObjectTexture(1, m_nmFlagTexture); // show tex on mask
			SetObjectMaterial(1, materialPath);
			SetObjectTexture(0, ""); // hide tex on hat
			SetObjectMaterial(0, ""); // hide mats on hat
			SetObjectTexture(2, m_nmFlagTexture); // apply on _g ( better safe then sorry )
			SetObjectMaterial(2, materialPath); // show mats on _g ( better safe then sorry )
 		}
	    else
		{
			SetObjectTexture(0, m_nmFlagTexture); // show tex on hat
			SetObjectMaterial(0, materialPath); // show mats on hat
			SetObjectTexture(1, ""); // hide tex on mask
			SetObjectMaterial(1, ""); // hide mats on mask
			SetObjectTexture(2, m_nmFlagTexture); // apply on _g ( better safe then sorry )
			SetObjectMaterial(2, materialPath); // show mats on _g ( better safe then sorry )
 		}
	    if (m_IsHeadgearVisible)
		{
			SetObjectTexture(0, m_nmFlagTexture); // show tex on hat
			SetObjectMaterial(0, materialPath); // show mats on hat
			SetObjectTexture(1, ""); // hide tex on mask
			SetObjectMaterial(1, ""); // hide mats on mask
			SetObjectTexture(2, m_nmFlagTexture); // apply on _g ( better safe then sorry )
			SetObjectMaterial(2, materialPath); // show mats on _g ( better safe then sorry )
		}
	    else
		{
			SetObjectTexture(1, ""); // show tex on mask
			SetObjectMaterial(1, ""); // show mats on mask
			SetObjectTexture(0, ""); // hide tex on hat
			SetObjectMaterial(0, ""); // hide mats on hat
			SetObjectTexture(2, m_nmFlagTexture); // apply on _g ( better safe then sorry )
			SetObjectMaterial(2, materialPath); // show mats on _g ( better safe then sorry )
		}
    }
	
    override void OnStoreSave(ParamsWriteContext ctx)
    {
        super.OnStoreSave(ctx);
        ctx.Write(m_nmFlagTexture); // save Flag Tex
		ctx.Write(m_nmFlagName); // Save Flag Name
        ctx.Write(m_IsMaskVisible); // Save visible Selecetion
        ctx.Write(m_IsHeadgearVisible); // Save visible Selecetion
    }

    override bool OnStoreLoad(ParamsReadContext ctx, int version)
    {
        if (!super.OnStoreLoad(ctx, version))
            return false;

        if (!ctx.Read(m_nmFlagTexture)) // load Flag Tex
            return false;

        if (!ctx.Read(m_nmFlagName)) // load Flag Name
            return false;

        if (!ctx.Read(m_IsMaskVisible)) 
            m_IsMaskVisible = false;
		
        if (!ctx.Read(m_IsHeadgearVisible)) 
            m_IsHeadgearVisible = false;
        return true;
    }
	
	override void AfterStoreLoad()
	{	
        super.AfterStoreLoad();
        ApplyVisibility();
	}

	void ApplyTexture(EntityAI parent, int slot_id)
	{
		if (GetGame().IsServer()) // on server for sync
		{
			PlayerBase player = PlayerBase.Cast(parent.GetHierarchyRootPlayer());
			if (player)
			{
				// Check for slot
				EntityAI hat = player.FindAttachmentBySlotName("Headgear");
				EntityAI backAttachment = player.FindAttachmentBySlotName("Mask");

				if (hat == this)
				{
					m_IsMaskVisible = false;
					m_IsHeadgearVisible = true;
					SetObjectTexture(0, m_nmFlagTexture); // show texture on hat
					SetObjectMaterial(0, materialPath); // show mats on hat
					SetObjectTexture(1, ""); // hide texture on mask
					SetObjectMaterial(1, ""); // hide mats on mask
					SetObjectTexture(2, m_nmFlagTexture); // apply on _g ( better safe then sorry )
					SetObjectMaterial(2, materialPath); // show mats on _g ( better safe then sorry )
				}
				else if (backAttachment == this)
				{
					m_IsMaskVisible = true;
					m_IsHeadgearVisible = false;
					SetObjectTexture(1, m_nmFlagTexture); // Show texture on mask
					SetObjectMaterial(1, materialPath); // show mats on mask
					SetObjectTexture(0, ""); // hide texture on hat
					SetObjectMaterial(0, ""); // hide mats on hat
					SetObjectTexture(2, m_nmFlagTexture); // apply on _g ( better safe then sorry )
					SetObjectMaterial(2, materialPath); // show mats on _g ( better safe then sorry )
				}
			}
			else
			{
					m_IsMaskVisible = false;
					m_IsHeadgearVisible = false;
					SetObjectTexture(1, ""); // Show texture on mask
					SetObjectMaterial(1, ""); // show mats on mask
					SetObjectTexture(0, ""); // hide texture on hat
					SetObjectMaterial(0, ""); // hide mats on hat
					SetObjectTexture(2, m_nmFlagTexture); // apply on _g ( better safe then sorry )
					SetObjectMaterial(2, materialPath); // show mats on _g ( better safe then sorry )
			}
		}
	}
	
	override void OnWasAttached(EntityAI parent, int slot_id)
	{
		super.OnWasAttached(parent, slot_id);
		m_lastAttachedSlot = slot_id; // store last attachment slot

		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(ApplyTexture, 50, false, this, m_lastAttachedSlot);
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(Synchronize, 60, false);
	}

	
	override void OnWasDetached(EntityAI parent, int slot_id)
	{
		super.OnWasDetached(parent, slot_id);
		m_lastAttachedSlot = slot_id; // store last attachment slot

		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(ApplyTexture, 50, false, this, m_lastAttachedSlot);
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(Synchronize, 60, false);
	}
	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionBandageTarget);
		AddAction(ActionBandageSelf);
		AddAction(ActionWringClothes);
	}
};