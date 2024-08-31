modded class PluginRecipesManagerBase extends PluginBase
{
	override void RegisterRecipies()
	{
		super.RegisterRecipies();
		
		RegisterRecipe(new nm_CraftArmbandRag);
		RegisterRecipe(new nm_CraftArmbandRaincoat);
		RegisterRecipe(new nm_CraftArmbandFlag);
    }       
};