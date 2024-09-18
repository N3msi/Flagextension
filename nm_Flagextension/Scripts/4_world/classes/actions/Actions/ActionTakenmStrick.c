
class ActionTakenmStickCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{	
		m_ActionData.m_ActionComponent = new CAContinuousTime(1.0);
	}
}

class ActionTakenmStick: ActionContinuousBase
{
	void ActionTakenmStick()
	{
		m_CallbackClass		= ActionTakenmStickCB;
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
		
		if (targetItem && targetItem.IsKindOf("nm_LongWoodenStick_deployed"))
		{
			return true;
		}
		return false;
	}	

	override void OnFinishProgressServer(ActionData action_data)
	{
		PlayerBase player = action_data.m_Player;
		nm_LongWoodenStick_deployed oldStick = nm_LongWoodenStick_deployed.Cast(action_data.m_Target.GetObject());

		if (player && oldStick)
		{
			EntityAI flagAttachment = oldStick.FindAttachmentBySlotName("Material_FPole_Flag");
			
			float oldStickHealth = oldStick.GetHealth("", "");
			float oldAttachmentHealth = flagAttachment.GetHealth("", "");

			string flagAttachmentType = "";
			if (flagAttachment)
			{
				flagAttachmentType = flagAttachment.GetType();
			}

			GetGame().ObjectDelete(oldStick);

			ItemBase newStick = ItemBase.Cast(action_data.m_Player.SpawnEntityOnGroundPos("LongWoodenStick", action_data.m_Player.GetPosition()));

			if (newStick)
			{
				newStick.SetHealth("", "", oldStickHealth);

				if (flagAttachmentType != "")
				{
					EntityAI newFlagAttachment = EntityAI.Cast(GetGame().CreateObject(flagAttachmentType, newStick.GetPosition()));
					
					if (newFlagAttachment)
					{
						newFlagAttachment.SetHealth("", "", oldAttachmentHealth);
					}
				}
			}
		}
	}
}		
		


