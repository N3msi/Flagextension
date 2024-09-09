modded class PluginRecipesManagerBase extends PluginBase
{
	override void RegisterRecipies()
	{
		super.RegisterRecipies();
		
		RegisterRecipe(new nm_CraftArmbandRag);
		RegisterRecipe(new nm_CraftArmbandRaincoat);
		RegisterRecipe(new nm_CraftArmbandFlag);
		RegisterRecipe(new nm_CraftBandanaRag);
		RegisterRecipe(new nm_CraftBandanaRaincoat);
		RegisterRecipe(new nm_CraftBandanaFlag);
		RegisterRecipe(new nm_DeCraftSlingbagDummy);
		RegisterRecipe(new nm_CraftSlingbagDummy);
		RegisterRecipe(new DeCraftnmImproBag);
		RegisterRecipe(new CraftnmImproBag);
    }       
};