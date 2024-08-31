class nm_ArmbandDummy extends Clothing
{
    private string m_nmFlagTexture; // Flag Texture
    private string m_nmFlagName; // Flag Name
	private string materialPathCape; // stored cape mats on EEHealthLevelChanged
	private string materialPathAB; // stored cape mats on EEHealthLevelChanged
	private string materialPathGround; // stored cape mats on EEHealthLevelChanged
    private int m_lastAttachedSlot; // attachement slot
    private bool m_IsCapeVisible; // store last shown selection
    private bool m_IsArmbandVisible; // store last shown selection
	
    void nm_ArmbandDummy()
    {
		SetObjectTexture(2, m_nmFlagTexture); // Apply tex on _g permanently
		SetObjectMaterial(2, materialPathGround); // show mats on _g ( better safe then sorry )
		ApplyVisibility()
    }
	
	void ~nm_ArmbandDummy()
    {	
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
                materialPathCape = "nm_Flagextension\\flag\\data\\nm_flag_cape_destruct.rvmat"; // Mat ruined
                materialPathAB = "nm_Flagextension\\flag\\data\\nm_ArmbandDummy_destruct.rvmat"; // Mat ruined
                materialPathGround = "nm_Flagextension\\flag\\data\\nm_Flag_folded_destruct.rvmat"; // Mat ruined
                break;
            case GameConstants.STATE_BADLY_DAMAGED:
            case GameConstants.STATE_DAMAGED:
                materialPathCape = "nm_Flagextension\\flag\\data\\nm_flag_cape_damage.rvmat"; // Mat badly damaged/damaged
                materialPathAB = "nm_Flagextension\\flag\\data\\nm_ArmbandDummy_damage.rvmat"; // Mat badly damaged/damaged
                materialPathGround = "nm_Flagextension\\flag\\data\\nm_Flag_folded_damage.rvmat"; // Mat badly damaged/damaged
                break;
            case GameConstants.STATE_WORN:
            case GameConstants.STATE_PRISTINE:
                materialPathCape = "nm_Flagextension\\flag\\data\\nm_flag_cape.rvmat"; // Mat worn/pristine
                materialPathAB = "nm_Flagextension\\flag\\data\\nm_ArmbandDummy.rvmat"; // Mat worn/pristine
                materialPathGround = "nm_Flagextension\\flag\\data\\nm_Flag_folded.rvmat"; // Mat worn/pristine
                break;
            default:
                materialPathCape = "nm_Flagextension\\flag\\data\\nm_flag_cape.rvmat"; // Fallback material
                materialPathAB = "nm_Flagextension\\flag\\data\\nm_ArmbandDummy.rvmat"; // Fallback material
                materialPathGround = "nm_Flagextension\\flag\\data\\nm_Flag_folded.rvmat"; // Fallback material
                break;
        }

        // Reapply visibility and material
        ApplyVisibility();
    }
	
	void ApplyVisibility()
    {
        if (m_IsCapeVisible)
		{
			SetObjectTexture(1, m_nmFlagTexture); // show tex on cape
			SetObjectMaterial(1, materialPathCape);
			SetObjectTexture(0, ""); // hide tex on armband
			SetObjectMaterial(0, ""); // hide mats on armband
			SetObjectTexture(2, m_nmFlagTexture); // apply on _g ( better safe then sorry )
			SetObjectMaterial(2, materialPathGround); // show mats on _g ( better safe then sorry )
 		}
	    else
		{
			SetObjectTexture(0, m_nmFlagTexture); // show tex on armband
			SetObjectMaterial(0, materialPathAB); // show mats on armband
			SetObjectTexture(1, ""); // hide tex on cape
			SetObjectMaterial(1, ""); // hide mats on cape
			SetObjectTexture(2, m_nmFlagTexture); // apply on _g ( better safe then sorry )
			SetObjectMaterial(2, materialPathGround); // show mats on _g ( better safe then sorry )
 		}
	    if (m_IsArmbandVisible)
		{
			SetObjectTexture(0, m_nmFlagTexture); // show tex on armband
			SetObjectMaterial(0, materialPathAB); // show mats on armband
			SetObjectTexture(1, ""); // hide tex on cape
			SetObjectMaterial(1, ""); // hide mats on cape
			SetObjectTexture(2, m_nmFlagTexture); // apply on _g ( better safe then sorry )
			SetObjectMaterial(2, materialPathGround); // show mats on _g ( better safe then sorry )
		}
	    else
		{
			SetObjectTexture(1, m_nmFlagTexture); // show tex on cape
			SetObjectMaterial(1, materialPathCape); // show mats on cape
			SetObjectTexture(0, ""); // hide tex on armband
			SetObjectMaterial(0, ""); // hide mats on armband
			SetObjectTexture(2, m_nmFlagTexture); // apply on _g ( better safe then sorry )
			SetObjectMaterial(2, materialPathGround); // show mats on _g ( better safe then sorry )
		}
    }
	
    override void OnStoreSave(ParamsWriteContext ctx)
    {
        super.OnStoreSave(ctx);
        ctx.Write(m_nmFlagTexture); // save Flag Tex
		ctx.Write(m_nmFlagName); // Save Flag Name
        ctx.Write(m_IsCapeVisible); // Save visible Selecetion
        ctx.Write(m_IsArmbandVisible); // Save visible Selecetion
    }

    override bool OnStoreLoad(ParamsReadContext ctx, int version)
    {
        if (!super.OnStoreLoad(ctx, version))
            return false;

        if (!ctx.Read(m_nmFlagTexture)) // load Flag Tex
            return false;

        if (!ctx.Read(m_nmFlagName)) // load Flag Name
            return false;

        if (!ctx.Read(m_IsCapeVisible)) 
            m_IsCapeVisible = false;
		
        if (!ctx.Read(m_IsArmbandVisible)) 
            m_IsArmbandVisible = false;
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
				EntityAI armband = player.FindAttachmentBySlotName("Armband");
				EntityAI backAttachment = player.FindAttachmentBySlotName("Back");

				if (armband == this)
				{
					m_IsCapeVisible = false;
					m_IsArmbandVisible = true;
					SetObjectTexture(0, m_nmFlagTexture); // show texture on armband
					SetObjectMaterial(0, materialPathAB); // show mats on armband
					SetObjectTexture(1, ""); // hide texture on cape
					SetObjectMaterial(1, ""); // hide mats on cape
					SetObjectTexture(2, m_nmFlagTexture); // apply on _g ( better safe then sorry )
					SetObjectMaterial(2, materialPathGround); // show mats on _g ( better safe then sorry )
				}
				else if (backAttachment == this)
				{
					m_IsCapeVisible = true;
					m_IsArmbandVisible = false;
					SetObjectTexture(1, m_nmFlagTexture); // Show texture on cape
					SetObjectMaterial(1, materialPathCape); // show mats on cape
					SetObjectTexture(0, ""); // hide texture on armband
					SetObjectMaterial(0, ""); // hide mats on armband
					SetObjectTexture(2, m_nmFlagTexture); // apply on _g ( better safe then sorry )
					SetObjectMaterial(2, materialPathGround); // show mats on _g ( better safe then sorry )
				}
			}
		}
	}
	
	override void OnWasAttached(EntityAI parent, int slot_id)
	{
		super.OnWasAttached(parent, slot_id);
		m_lastAttachedSlot = slot_id; // store last attachment slot

		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(ApplyTexture, 50, false, this);
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(Synchronize, 60, false);
	}

	
	override void OnWasDetached(EntityAI parent, int slot_id)
	{
		super.OnWasDetached(parent, slot_id);

		if (m_nmFlagName != "") // 0-Check, no Lambda if 0
		{
			PlayerBase player = PlayerBase.Cast(parent.GetHierarchyRootPlayer());

			if (player && GetGame().IsServer()) // on Server for sync
			{
				EntityAI backAttachment = player.FindAttachmentBySlotName("Back");
				EntityAI armbandAttachment = player.FindAttachmentBySlotName("Armband");

				if (backAttachment != this && armbandAttachment != this)
				{
					TurnItemIntoItemLambda turnLambda = new TurnItemIntoItemLambda(this, m_nmFlagName, player); // Use vanilla Lambda to create item from stored flagname
					turnLambda.SetTransferParams(true, true, true, false); // Transfer properties
					turnLambda.Execute();
				}
			}
		}
	}
}