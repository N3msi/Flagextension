modded class PluginRecipesManagerBase 
{
     override void RegisterRecipies()
    {
        super.RegisterRecipies();
		UnregisterRecipe("CraftArmbandFlag"); // delete old Recipe for crafting armbands from flag
		UnregisterRecipe("CraftArmbandRag"); // delete old Recipe for crafting armbands from flag
		UnregisterRecipe("CraftArmbandRaincoat"); // delete old Recipe for crafting armbands from flag
		//TODO: delete old Recipe for crafting armbands from Raincapes/Rags
	}
}