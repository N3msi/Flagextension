modded class Hologram
{
    override string ProjectionBasedOnParent()
    {
        Flag_Base Flag = Flag_Base.Cast( m_Player.GetHumanInventory().GetEntityInHands() );
		
        if (Flag)
        {
            return Flag.GetHolo();
        }
		
		LongWoodenStick Stick = LongWoodenStick.Cast(m_Player.GetHumanInventory().GetEntityInHands());
        if (Stick)
        {
            return Stick.GetHolo(); // Assuming LongWoodenStick has a GetHolo() method
        }
		
        return super.ProjectionBasedOnParent();
    }
}

class nmPlaceFlagonGround : TurnItemIntoItemLambda
{
	protected vector m_Orientation;
	protected float m_FlagHealth;
	protected string m_FlagTexture;
	protected string m_FlagName;

	void nmPlaceFlagonGround(EntityAI old_item, string new_item_type, PlayerBase player, vector position, vector orientation)
	{
		InventoryLocation il = new InventoryLocation();

		vector mat[4];
		Math3D.MatrixIdentity4(mat);
		mat[3] = position;

		il.SetGround(null, mat);
		OverrideNewLocation(il);

		m_Orientation = orientation;
		m_FlagHealth = old_item.GetHealth("", "");
		m_FlagTexture = old_item.GetHiddenSelectionsTextures()[0];
		m_FlagName = old_item.GetType();
	}

    override void OnSuccess(EntityAI new_item)
    {
        super.OnSuccess(new_item);

		nm_Flag_deployed flagItem;
		if (nm_Flag_deployed.CastTo(flagItem, new_item))
		{
			// transfer ori
			flagItem.SetOrientation(m_Orientation);
			flagItem.OnPlacementComplete(m_Player, flagItem.GetPosition(), m_Orientation);
			
			// transfer health
			flagItem.SetHealth("", "", m_FlagHealth);
			
			// transfer tex
			flagItem.SetnmFlagTexture(m_FlagTexture);

			// transfer flagname
			flagItem.SetnmFlagName(m_FlagName);
		}
    }    

	protected override void RemoveOldItemFromLocation()
	{
		super.RemoveOldItemFromLocation();

		m_Player.GetHumanInventory().OnEntityInHandsDestroyed(m_OldLocation);
	}
}

class nmPlaceStickonGround : TurnItemIntoItemLambda
{
	protected vector m_Orientation;
	protected float m_FlagHealth;
	protected string m_FlagTexture;
	protected string m_FlagName;

	void nmPlaceStickonGround(EntityAI old_item, string new_item_type, PlayerBase player, vector position, vector orientation)
	{
		InventoryLocation il = new InventoryLocation();

		vector mat[4];
		Math3D.MatrixIdentity4(mat);
		mat[3] = position;

		il.SetGround(null, mat);
		OverrideNewLocation(il);

		m_Orientation = orientation;
		m_FlagHealth = old_item.GetHealth("", "");
	}

    override void OnSuccess(EntityAI new_item)
    {
        super.OnSuccess(new_item);

		nm_Flag_deployed flagItem;
		if (nm_Flag_deployed.CastTo(flagItem, new_item))
		{
			// transfer ori
			flagItem.SetOrientation(m_Orientation);
			flagItem.OnPlacementComplete(m_Player, flagItem.GetPosition(), m_Orientation);
			
			// transfer health
			flagItem.SetHealth("", "", m_FlagHealth);
		}
    }    

	protected override void RemoveOldItemFromLocation()
	{
		super.RemoveOldItemFromLocation();

		m_Player.GetHumanInventory().OnEntityInHandsDestroyed(m_OldLocation);
	}
}