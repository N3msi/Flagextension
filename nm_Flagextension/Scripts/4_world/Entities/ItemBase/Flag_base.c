void CreatenmArmband(EntityAI parent, string nmFlagTexture, string nmFlagName, float nmFlagHealth, int slot_id)
{
    if (GetGame().IsServer()) // Serverside for better synch
    {
        PlayerBase player = PlayerBase.Cast(parent);
        if (player)
        {			
            // Safely cast the result of CreateInInventory to nm_ArmbandDummy
            nm_ArmbandDummy new_item = nm_ArmbandDummy.Cast(player.GetInventory().CreateInInventory("nm_ArmbandDummy"));
            
            if (new_item) // Check if the casting was successful
            {
                new_item.SetnmFlagName(nmFlagName); // transfer flagname
                new_item.SetnmFlagTexture(nmFlagTexture); // transfer flagtex
                new_item.SetHealth("", "", nmFlagHealth); // transfer health
            }
        }
    }
}

modded class Hologram
{
    override string ProjectionBasedOnParent()
    {
        Flag_Base Flag = Flag_Base.Cast( m_Player.GetHumanInventory().GetEntityInHands() );

        if (Flag)
        {
            return Flag.GetHolo();
        }
        return super.ProjectionBasedOnParent();
    }
}

modded class Flag_Base
{
	ref protected EffectSound m_DeployLoopSound;
    private string m_nmFlagTexture; // stored Flag Tex
	private string materialPathfolded; // stored materialbased on EEHealthLevelChanged
	private string materialPathunfolded; // stored materialbased on EEHealthLevelChanged
    private bool m_Isfolded; // Save visible selection
    private bool m_Isunfolded; // Save visible selection
	
	void Flag_Base()
	{
		string m_nmFlagTexture = GetHiddenSelectionsTextures()[0]; // Get FlagTexture
		m_Isunfolded = false;
		m_Isfolded = true;
		ApplyVisibility();
	}
	
	void ~Flag_Base()
	{
	}

    string GetnmFlagTexture()
    {
        return m_nmFlagTexture;
    }
	
	// --- SYNCHRONIZATION
	void Synchronize()
	{
		if ( GetGame().IsServer() )
		{
			SetSynchDirty();
		}
	}

	override void EEHealthLevelChanged(int oldLevel, int newLevel, string zone) 	///bypassing damagesys to apply Material
    {
        super.EEHealthLevelChanged(oldLevel, newLevel, zone);

        switch (newLevel)
        {
            case GameConstants.STATE_RUINED:
                materialPathfolded = "nm_Flagextension\\flag\\data\\nm_flag_folded_destruct.rvmat"; // Mat ruined
                materialPathunfolded = "nm_Flagextension\\flag\\data\\nm_flag_unfolded_destruct.rvmat"; // Mat ruined
                break;
            case GameConstants.STATE_BADLY_DAMAGED:
            case GameConstants.STATE_DAMAGED:
                materialPathfolded = "nm_Flagextension\\flag\\data\\nm_flag_folded_damage.rvmat"; // Mat badly damaged/damaged
                materialPathunfolded = "nm_Flagextension\\flag\\data\\nm_flag_unfolded_damage.rvmat"; // Mat badly damaged/damaged
                break;
            case GameConstants.STATE_WORN:
            case GameConstants.STATE_PRISTINE:
                materialPathfolded = "nm_Flagextension\\flag\\data\\nm_flag_folded.rvmat"; // Mat worn/pristine
                materialPathunfolded = "nm_Flagextension\\flag\\data\\nm_flag_unfolded.rvmat"; // Mat worn/pristine
                break;
            default:
                materialPathfolded = "nm_Flagextension\\flag\\data\\nm_flag_folded.rvmat"; // Fallback material
                materialPathunfolded = "nm_Flagextension\\flag\\data\\nm_flag_folded.rvmat"; // Fallback material
                break;
        }

        // Reapply visibility and material
        ApplyVisibility();
    }
	
	void ApplyVisibility()
    {
        if (m_Isfolded)
        {
			ShowSelection("folded");
			HideSelection("unfolded");
        }
        else
        {
			HideSelection("folded");
			ShowSelection("unfolded");
        }
        if (m_Isunfolded)
        {
			HideSelection("folded");
			ShowSelection("unfolded");
        }
        else
        {
			ShowSelection("folded");
			HideSelection("unfolded");
        }
    }
	
	// --- EVENTS
    override void OnStoreSave(ParamsWriteContext ctx)
    {
        super.OnStoreSave(ctx);
        ctx.Write(m_nmFlagTexture); // Save Flag Tex
        ctx.Write(m_Isfolded); // Save visible selection
        ctx.Write(m_Isunfolded); // Save visible selection
    }

    override bool OnStoreLoad(ParamsReadContext ctx, int version)
    {
        if (!super.OnStoreLoad(ctx, version))
            return false;

        if (!ctx.Read(m_nmFlagTexture))
            return false;

        if (!ctx.Read(m_Isfolded))
            m_Isfolded = false;

        if (!ctx.Read(m_Isunfolded))
            m_Isunfolded = false;
		
        return true;
    }

	override void AfterStoreLoad()
	{	
		super.AfterStoreLoad();
		ApplyVisibility();		
	}
	
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();

		if (IsDeploySound())
		{
			PlayDeploySound();
		}

		if (CanPlayDeployLoopSound())
		{
			PlayDeployLoopSound();
		}
		ApplyVisibility();
	}

	void DeletenmFlag(EntityAI flag)
	{
		if (flag)
		{
			GetGame().ObjectDelete(flag); 
		}
	}
	
	override void OnWasAttached(EntityAI parent, int slot_id)
	{
		super.OnWasAttached(parent,slot_id);

		string nmFlagTexture = GetHiddenSelectionsTextures()[0]; // Get FlagTexture	
		string nmFlagName = this.GetType(); // get FlagName
		float nmFlagHealth = this.GetHealth(); // get Flag Health
		
		if (parent.IsKindOf("TerritoryFlag"))
		{	
			m_Isfolded = false;
			m_Isunfolded = true;
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(ApplyVisibility, 50, false, this, slot_id);
		}
		else if (parent.IsKindOf("SurvivorBase"))
		{
			EntityAI ABSlot = parent.FindAttachmentBySlotName("armband");
			EntityAI BackSlot = parent.FindAttachmentBySlotName("back");			

			if ((ABSlot && ABSlot.IsKindOf("Flag_Base")) || (BackSlot && BackSlot.IsKindOf("Flag_Base")))
			{
			// create armband later to prevent bugged slot
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(CreatenmArmband, 100, false, parent, nmFlagTexture, nmFlagName, nmFlagHealth, slot_id);

			// delete flag fist to prevent bugged slot
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(DeletenmFlag, 50, false, this);
			}
		}
	}

	override void OnWasDetached(EntityAI parent, int slot_id)
	{
		super.OnWasDetached(parent,slot_id);
		
		m_Isfolded = true;
		m_Isunfolded = false;
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(ApplyVisibility, 50, false, this, slot_id);		
	}
	
	override void OnPlacementComplete(Man player, vector position = "0 0 0", vector orientation = "0 0 0")
	{
		super.OnPlacementComplete(player, position, orientation);

		if (GetGame().IsServer() || !GetGame().IsMultiplayer())
		{
			nmPlaceFlagonGround lambda = new nmPlaceFlagonGround(this, GetItem(), PlayerBase.Cast(player), position, orientation);
			player.ServerReplaceItemInHandsWithNewElsewhere(lambda);
		}

		SetIsDeploySound(true);
	}

	override bool IsDeployable()
	{
		return true;
	}

	override bool IsBasebuildingKit()
	{
		return true;
	}
	
	override string GetDeploySoundset()
	{
		return "putDown_FenceKit_SoundSet";
	}

	void PlayDeployLoopSound()
	{
		if (GetGame().IsClient() || !GetGame().IsMultiplayer())
		{
			m_DeployLoopSound = SEffectManager.PlaySound(GetLoopDeploySoundset(), GetPosition());
		}
	}
	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionAttach);
		AddAction(ActionTogglePlaceObject);	
		AddAction(ActionPlaceObject);
	}
	
    string GetItem()
    {
        return "nm_Flag_deployed";
    }
	
	string GetHolo()
    {
        return "nm_Flag_placing";
    }
}
