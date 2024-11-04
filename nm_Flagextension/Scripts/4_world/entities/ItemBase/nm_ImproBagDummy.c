class nm_ImproBagDummy extends Clothing
{
	private string m_nmFlagTexture; // Flag Texture
    private string m_nmFlagName;
	private string materialPath;	// Flag Name

	void nm_ImproBagDummy()
	{
	}
	
	void ~nm_ImproBagDummy()
	{
	}

	override bool CanHaveWetness()
	{
		return false;
	}
	
	void SetFlagAttributes(string texturePath, string nmFlagName)
    {
        m_nmFlagTexture = texturePath;
        m_nmFlagName = nmFlagName;
    }

    void SetnmFlagName(string name)
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
	
    void SetnmFlagTexture(string texturePath)
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
                materialPath = "nm_Flagextension\\flag\\data\\nm_flag_folded_destruct.rvmat"; // Mat ruined
                break;
            case GameConstants.STATE_BADLY_DAMAGED:
            case GameConstants.STATE_DAMAGED:
                materialPath = "nm_Flagextension\\flag\\data\\nm_flag_folded_damage.rvmat"; // Mat badly damaged/damaged
                break;
            case GameConstants.STATE_WORN:
            case GameConstants.STATE_PRISTINE:
                materialPath = "nm_Flagextension\\flag\\data\\nm_flag_folded.rvmat"; // Mat worn/pristine
                break;
            default:
                materialPath = "nm_Flagextension\\flag\\data\\nm_flag_folded.rvmat"; // Fallback material
                break;
        }

        // Reapply visibility and material
        ApplyVisibility();
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
	
    override void OnVariablesSynchronized()
    {
        super.OnVariablesSynchronized();
        ApplyVisibility();
    }

    override void OnStoreSave(ParamsWriteContext ctx)
    {
        super.OnStoreSave(ctx);
        ctx.Write(m_nmFlagTexture); // Save Flag Tex
		ctx.Write(m_nmFlagName); // Save Flag Tex
    }

    override bool OnStoreLoad(ParamsReadContext ctx, int version)
    {
        if (!super.OnStoreLoad(ctx, version))
            return false;

        if (!ctx.Read(m_nmFlagTexture))
            return false;
		
        if (!ctx.Read(m_nmFlagName)) // load Flag Name
            return false;
		
        return true;
    }

    override void AfterStoreLoad()
    {
        super.AfterStoreLoad();
        ApplyVisibility();
    }
};