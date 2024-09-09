modded class ModItemRegisterCallbacks
{

    override void RegisterHeavy(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
    {
		pType.AddItemInHandsProfileIK("nm_CraftArmbandRag", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", pBehavior,    "dz/anims/anm/player/ik/heavy/55galDrum.anm"); 
		pType.AddItemInHandsProfileIK("nm_CraftArmbandFlag", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", pBehavior,    "dz/anims/anm/player/ik/heavy/55galDrum.anm"); 
		pType.AddItemInHandsProfileIK("nm_CraftArmbandRaincoat", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", pBehavior,    "dz/anims/anm/player/ik/heavy/55galDrum.anm"); 
		pType.AddItemInHandsProfileIK("nm_CraftBandanaRag", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", pBehavior,    "dz/anims/anm/player/ik/heavy/55galDrum.anm"); 
		pType.AddItemInHandsProfileIK("nm_CraftBandanaFlag", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", pBehavior,    "dz/anims/anm/player/ik/heavy/55galDrum.anm"); 
		pType.AddItemInHandsProfileIK("nm_CraftBandanaRaincoat", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", pBehavior,    "dz/anims/anm/player/ik/heavy/55galDrum.anm"); 
		pType.AddItemInHandsProfileIK("nm_DeCraftSlingbagDummy", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", pBehavior,    "dz/anims/anm/player/ik/heavy/55galDrum.anm"); 
		pType.AddItemInHandsProfileIK("nm_CraftSlingbagDummy", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", pBehavior,    "dz/anims/anm/player/ik/heavy/55galDrum.anm"); 
		pType.AddItemInHandsProfileIK("DeCraftnmImproBag", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", pBehavior,    "dz/anims/anm/player/ik/heavy/55galDrum.anm"); 
		pType.AddItemInHandsProfileIK("CraftnmImproBag", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", pBehavior,    "dz/anims/anm/player/ik/heavy/55galDrum.anm"); 

	    super.RegisterHeavy(pType, pBehavior);
    }

}