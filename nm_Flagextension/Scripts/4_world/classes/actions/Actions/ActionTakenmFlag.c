modded class PlayerBase
{
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionTakenmFlag);
	}
};

class ActionTakenmFlagCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{	
		m_ActionData.m_ActionComponent = new CAContinuousTime(1.0);
	}
}

class ActionTakenmFlag: ActionContinuousBase
{
	void ActionTakenmFlag()
	{
		m_CallbackClass		= ActionTakenmFlagCB;
		m_CommandUID 		= DayZPlayerConstants.CMD_ACTIONFB_CRAFTING;
		m_FullBody 			= true;
		m_StanceMask 		= DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight 	= UASoftSkillsWeight.ROUGH_HIGH;
		m_Text 				= "#fold";
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionTarget	= new CCTObject(UAMaxDistances.DEFAULT);
		m_ConditionItem 	= new CCINotPresent();
		m_Sound = "nm_Folding_Sound";
	}
	
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		ItemBase targetItem = ItemBase.Cast(target.GetObject());
		
		if (targetItem.IsKindOf("nm_Flag_deployed") && targetItem.IsEmpty() )
		{
			return true;
		} 
		return false;
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		PlayerBase player = action_data.m_Player;
		nm_Flag_deployed oldFlag = nm_Flag_deployed.Cast(action_data.m_Target.GetObject());

		if (player && oldFlag)
		{
			float oldFlagHealth = oldFlag.GetHealth("", "");
			string flagName = oldFlag.GetnmFlagName();

			GetGame().ObjectDelete(oldFlag);

			// Spawn the new flag using the flagName
			ItemBase newFlag = ItemBase.Cast(action_data.m_Player.SpawnEntityOnGroundPos(flagName, action_data.m_Player.GetPosition()));

			if (newFlag)
			{
				newFlag.SetHealth("", "", oldFlagHealth);
			}
		}
	}
	
}		
		


