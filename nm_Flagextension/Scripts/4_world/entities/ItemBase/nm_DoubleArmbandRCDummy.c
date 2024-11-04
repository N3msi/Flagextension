class nm_DoubleArmbandRCDummy extends Clothing
{
    private string m_nmFlagTexture; // stored Flag Tex
	private string materialPath; // stored materialbased on EEHealthLevelChanged
    private bool m_IsBigVisible; // Save visible selection
    private bool m_IsSmallVisible; // Save visible selection

    void nm_DoubleArmbandRCDummy()
    {
		ApplyVisibility();
    }

    void ~nm_DoubleArmbandRCDummy()
    {
    }

	override bool CanHaveWetness()
	{
		return false;
	}
	
    override bool CanPutInCargo(EntityAI parent)
    {
        if (!super.CanPutInCargo(parent)) { return false; }
        if (GetNumberOfItems() == 0 || !parent || parent.IsMan())
        {
            return true;
        }
        return false;
    }

    override bool CanPutAsAttachment(EntityAI parent)
    {
        if (!super.CanPutAsAttachment(parent)) { return false; }
        if (GetQuantity() <= 1)
        {
            return true;
        }
        return false;
    }

    override void SetActions()
    {
        super.SetActions();
        AddAction(ActionWringClothes);
    }
	
	override void EEHealthLevelChanged(int oldLevel, int newLevel, string zone) 	///bypassing damagesys to apply Material
    {
        super.EEHealthLevelChanged(oldLevel, newLevel, zone);

        switch (newLevel)
        {
            case GameConstants.STATE_RUINED:
                materialPath = "nm_Flagextension\\flag\\data\\nm_ArmbandDoubleRC_destruct.rvmat"; // Mat ruined
                break;
            case GameConstants.STATE_BADLY_DAMAGED:
            case GameConstants.STATE_DAMAGED:
                materialPath = "nm_Flagextension\\flag\\data\\nm_ArmbandDoubleRC_damage.rvmat"; // Mat badly damaged/damaged
                break;
            case GameConstants.STATE_WORN:
            case GameConstants.STATE_PRISTINE:
                materialPath = "nm_Flagextension\\flag\\data\\nm_ArmbandDoubleRC.rvmat"; // Mat worn/pristine
                break;
            default:
                materialPath = "nm_Flagextension\\flag\\data\\nm_ArmbandDoubleRC.rvmat"; // Fallback material
                break;
        }

        // Reapply visibility and material
        ApplyVisibility();
    }
	
    string GetnmFlagTexture()
    {
        return m_nmFlagTexture;
    }

    void SetnmFlagTexture(string texturePath) //used to transfer tex from recipe
    {
        m_nmFlagTexture = texturePath;
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
        if (m_IsBigVisible)
        {
            SetObjectTexture(1, m_nmFlagTexture); // show tex on big
			SetObjectMaterial(1, materialPath); // show mats on big
            SetObjectTexture(0, ""); // hide tex on small
			SetObjectMaterial(0, ""); // hide mats on small
            SetObjectTexture(2, m_nmFlagTexture); // _g tex
			SetObjectMaterial(2, materialPath); //  _g mat
        }
        else
        {
            SetObjectTexture(0, m_nmFlagTexture); // show tex on small
			SetObjectMaterial(0, materialPath); // show mats on small
            SetObjectTexture(1, ""); // hide tex on big
			SetObjectMaterial(1, ""); // hide mats on big
            SetObjectTexture(2, m_nmFlagTexture); // _g tex
			SetObjectMaterial(2, materialPath); // apply mats on small
        }
        if (m_IsSmallVisible)
        {
            SetObjectTexture(0, m_nmFlagTexture); // show tex on small
			SetObjectMaterial(0, materialPath); // show mats on small
            SetObjectTexture(1, ""); // hide tex on big
			SetObjectMaterial(1, ""); // hide mats on big
            SetObjectTexture(2, m_nmFlagTexture); // _g tex
			SetObjectMaterial(2, materialPath); // apply mats on small
        }
        else
        {
            SetObjectTexture(1, m_nmFlagTexture); // show tex on big
			SetObjectMaterial(1, materialPath); // show mats on big
            SetObjectTexture(0, ""); // hide tex on small
			SetObjectMaterial(0, ""); // hide mats on small
            SetObjectTexture(2, m_nmFlagTexture); // _g tex
			SetObjectMaterial(2, materialPath); //  _g mat
        }
    }

    override void OnStoreSave(ParamsWriteContext ctx)
    {
        super.OnStoreSave(ctx);
        ctx.Write(m_nmFlagTexture); // Save Flag Tex
        ctx.Write(m_IsBigVisible); // Save visible selection
        ctx.Write(m_IsSmallVisible); // Save visible selection
    }

    override bool OnStoreLoad(ParamsReadContext ctx, int version)
    {
        if (!super.OnStoreLoad(ctx, version))
            return false;

        if (!ctx.Read(m_nmFlagTexture))
            return false;

        if (!ctx.Read(m_IsBigVisible))
            m_IsBigVisible = false;

        if (!ctx.Read(m_IsSmallVisible))
            m_IsSmallVisible = false;
		
        return true;
    }

    override void AfterStoreLoad()
    {
        super.AfterStoreLoad();
        ApplyVisibility();
    }

	void ApplyTexture(EntityAI parent, int slot_id = -1)
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
			
			if (player)
			{
				if (player.FindAttachmentBySlotName("Body")) // check for Clothing_Tops
				{
					m_IsBigVisible = true;
					m_IsSmallVisible = false;
					SetObjectTexture(1, m_nmFlagTexture); // show tex on big
					SetObjectMaterial(1, materialPath); // show mats on big
					SetObjectTexture(0, ""); // hide tex on small
					SetObjectMaterial(0, ""); // hide mats on small
					SetObjectTexture(2, m_nmFlagTexture); // _g tex
					SetObjectMaterial(2, materialPath); // _g mat
				}
				else
				{
					m_IsBigVisible = false;
					m_IsSmallVisible = true;
					SetObjectTexture(0, m_nmFlagTexture); // show tex on small
					SetObjectMaterial(0, materialPath); // show mats on small
					SetObjectTexture(1, ""); // hide tex on big
					SetObjectMaterial(1, ""); // hide mats on big
					SetObjectTexture(2, m_nmFlagTexture); // _g tex
					SetObjectMaterial(2, materialPath); // _g mat
				}
			}
		}
	}


	override void OnWasAttached(EntityAI parent, int slot_id)
	{
		super.OnWasAttached(parent, slot_id);
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(ApplyTexture, 50, false, this, slot_id);
	}

	override void OnWasDetached(EntityAI parent, int slot_id)
	{
		super.OnWasDetached(parent, slot_id);
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(ApplyTexture, 50, false, this, slot_id);
	}

	override void SwitchItemSelectionTextureEx(EItemManipulationContext context, Param par = null)
	{
		super.SwitchItemSelectionTextureEx(context, par);
		if (context == EItemManipulationContext.ATTACHING || context == EItemManipulationContext.UPDATE)
		{
			EntityAI parent = GetHierarchyParent();
			int defaultSlotID = -1;
			if (parent)
			{
				ApplyTexture(parent, defaultSlotID);
			}
		}
	}
}