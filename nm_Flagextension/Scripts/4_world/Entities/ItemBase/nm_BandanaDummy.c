class nm_BandanaDummy: Clothing
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionBandageTarget);
		AddAction(ActionBandageSelf);
		AddAction(ActionWringClothes);
	}
	
	void nm_BandanaDummy()
	{

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
};