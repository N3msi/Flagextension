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
	private string materialPathfolded; // stored materialbased on EEHealthLevelChanged
	private string materialPathunfolded; // stored materialbased on EEHealthLevelChanged
	
	void Flag_Base()
	{
		UpdateVisualState()
	}
	
	void ~Flag_Base()
	{
	}
	
	// --- SYNCHRONIZATION
	void Synchronize()
	{
		if ( GetGame().IsServer() )
		{
			SetSynchDirty();
		}
	}

    override void EEInit()
    {
        super.EEInit();

		UpdateVisualState()
    }
	
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
	}
	
	// --- EVENTS
	override void OnStoreSave( ParamsWriteContext ctx )
	{   
		super.OnStoreSave( ctx );
	}
	
	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version))
			return false;

		EntityAI parent = GetHierarchyParent();

		// Check if attached and if attached to player
		if (parent.IsKindOf("TerritoryFlag"))
		{
			SetObjectMaterial(0, materialPathunfolded);
		}
		else
		{
			SetObjectMaterial(0, materialPathfolded);
		}

		return true;
	}
	
	override void AfterStoreLoad()
	{	
		super.AfterStoreLoad();
				
	}

	void UpdateVisualState()
	{	
		EntityAI parent = GetHierarchyParent();
	
		if (parent && parent.IsKindOf("TerritoryFlag")
		{
			SetObjectMaterial(0, materialPathunfolded);
			ShowSelection("unfolded");
			HideSelection("folded");
		}
		else
		{
			SetObjectMaterial(0, materialPathfolded);
			ShowSelection("folded");
			HideSelection("unfolded");
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
                materialPathunfolded = "nm_Flagextension\\flag\\data\\nm_flag_unfolded.rvmat"; // Fallback material
                break;
        }	
		UpdateVisualState()
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
		
		if (parent && parent.IsKindOf("SurvivorBase"))
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
		else
		{	
			SetObjectMaterial(0, materialPathunfolded); // mats tex on unfolded
			ShowSelection("unfolded");
			HideSelection("folded");
		}
	}

	override void OnWasDetached(EntityAI parent, int slot_id)
	{
		super.OnWasDetached(parent,slot_id);
		
		SetObjectMaterial(0, materialPathfolded); // mats tex on unfolded
		ShowSelection("folded");
		HideSelection("unfolded");	
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
	
	override int GetViewIndex()
	{
		if ( MemoryPointExists( "invView2" ) )
		{		
			InventoryLocation il = new InventoryLocation;
			GetInventory().GetCurrentInventoryLocation( il );
			InventoryLocationType type = il.GetType();
			switch ( type )
			{
				case InventoryLocationType.ATTACHMENT:
				{
					return 1;
				}
				default:
				{
					return 0;
				}
			}
		}
		return 0;
	}
}


