class nm_CarflagDummy extends ItemBase
{
	private string m_nmFlagTexture; // Flag Texture
	private string materialPath;	// Flag Name

	override void AfterStoreLoad()
	{	
       super.AfterStoreLoad();
       GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(DeleteOnRestart, 50, false);  // Kill AddChild Dummy each restart/relog / EEItemAttached creates a new one each restart/relog
	}

	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		
        ApplyVisibility();
	}

	void DeleteOnRestart()
	{
		if (GetGame().IsServer() && !GetGame().IsClient())
		{
			GetGame().ObjectDelete(this);
		}
	}
	
	void SetFlagAttributes(string texturePath, string nmFlagName)
    {
        m_nmFlagTexture = texturePath;
    }

	string GetnmFlagTexture()
    {
        return m_nmFlagTexture;
    }
	
    void SetnmFlagTexture(string texturePath) // sets tex from nmPlaceFlagonGround
    {
        m_nmFlagTexture = texturePath;
        ApplyVisibility(); 
    }

	override void EEHealthLevelChanged(int oldLevel, int newLevel, string zone) 	///bypassing damagesys to apply Material
    {
        super.EEHealthLevelChanged(oldLevel, newLevel, zone);

        switch (newLevel)
        {
            case GameConstants.STATE_RUINED:
                materialPath = "nm_Flagextension\\flag\\data\\nm_stickflag_destruct.rvmat"; // Mat ruined
                break;
            case GameConstants.STATE_BADLY_DAMAGED:
            case GameConstants.STATE_DAMAGED:
                materialPath = "nm_Flagextension\\flag\\data\\nm_stickflag_damage.rvmat"; // Mat badly damaged/damaged
                break;
            case GameConstants.STATE_WORN:
            case GameConstants.STATE_PRISTINE:
                materialPath = "nm_Flagextension\\flag\\data\\nm_stickflag.rvmat"; // Mat worn/pristine
                break;
            default:
                materialPath = "nm_Flagextension\\flag\\data\\nm_stickflag.rvmat"; // Fallback material
                break;
        }
		SetAttachmentHealth(newLevel);
        ApplyVisibility();
    }

	void SetAttachmentHealth(int newHealthLevel)
    {
		if (GetGame().IsServer())
        {
			EntityAI parent = EntityAI.Cast(GetParent());
			
			if (parent && parent.IsInherited(CarScript))
			{
				ItemBase attachedFlag = ItemBase.Cast(parent.FindAttachmentBySlotName("Material_FPole_Flag"));
				
				if (attachedFlag)
				{
					// synch health of attached flag with dummy
					switch (newHealthLevel)
					{
						case GameConstants.STATE_RUINED:
							attachedFlag.SetHealth(0);
							break;
						case GameConstants.STATE_BADLY_DAMAGED:
							attachedFlag.SetHealth(attachedFlag.GetMaxHealth() * 0.2);
							break;
						case GameConstants.STATE_DAMAGED:
							attachedFlag.SetHealth(attachedFlag.GetMaxHealth() * 0.5);
							break;
						case GameConstants.STATE_WORN:
							attachedFlag.SetHealth(attachedFlag.GetMaxHealth() * 0.8);
							break;
						case GameConstants.STATE_PRISTINE:
							attachedFlag.SetHealth(attachedFlag.GetMaxHealth());
							break;
						default:
							break;
					}
				}
			}
		}
    }
	
    private void ApplyVisibility()
    {
        if (m_nmFlagTexture != "") 
        {
            SetObjectTexture(0, m_nmFlagTexture);
			SetObjectMaterial(0, materialPath);
        }
    }

    void Synchronize()
    {
        if (GetGame().IsServer())
        {
            SetSynchDirty();
        }
    }
	
	override bool IsHologram()
	{
		return true;
	}
	
	override bool CanPutInCargo( EntityAI parent )
    {
        return false;
    }
 
	override bool CanPutIntoHands( EntityAI parent )
	{
		return false;
	}

}