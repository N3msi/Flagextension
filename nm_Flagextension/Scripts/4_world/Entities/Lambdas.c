class nmTurnArmbandToFlag : TurnItemIntoItemLambda
{
	void nmTurnArmbandToFlag(EntityAI old_item, string new_item_type, PlayerBase player)
	{
		SetTransferParams();
	}

    override void OnSuccess(EntityAI new_item)
    {
        super.OnSuccess(new_item);

		Flag_Base flagItem;
		if (Flag_Base.CastTo(flagItem, new_item))
		{
			flagItem.UpdateVisualState();
		}
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
			// Set orientation and health
			flagItem.SetOrientation(m_Orientation);
			flagItem.SetHealth("", "", m_FlagHealth);
			flagItem.OnPlacementComplete(m_Player, flagItem.GetPosition(), m_Orientation);

			// Apply the texture to the new item
			flagItem.SetnmFlagTexture(m_FlagTexture);

			// Set the flag name on the new item
			flagItem.SetnmFlagName(m_FlagName);
		}
    }    

	protected override void RemoveOldItemFromLocation()
	{
		super.RemoveOldItemFromLocation();

		m_Player.GetHumanInventory().OnEntityInHandsDestroyed(m_OldLocation);
	}
}
