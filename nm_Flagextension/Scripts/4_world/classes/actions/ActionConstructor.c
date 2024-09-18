modded class ActionConstructor
{	
	override void RegisterActions(TTypenameArray actions)
	{
		super.RegisterActions(actions);
		
		actions.Insert(ActionTakenmFlag);
		actions.Insert(ActionTakenmStick);
	}
};  