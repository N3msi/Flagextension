modded class SharpenLongStick
{	
	override bool CanDo(ItemBase ingredients[], PlayerBase player)//final check for recipe's validity
	{
		ItemBase ingredient1 = ingredients[0];
		
		if ( ingredient1.IsEmpty() )
		{
			return true;
		}
		else
		{
			return false;	
		}
	}
};
