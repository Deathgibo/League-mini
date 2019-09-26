#include "TowerAttackingPlayerState.h"
#include "TowerIdleState.h"

TowerAttackingPlayerState::TowerAttackingPlayerState()
{

}
TowerState* TowerAttackingPlayerState::handleinput(Tower& tower)
{
	if (tower.playertarget == NULL || tower.playertarget->currenthealth <= 0)
	{
		return new TowerIdleState();
	}
	if (sqrt(pow(tower.MapPosition.x - tower.playertarget->MapPosition.x, 2) + pow(tower.MapPosition.y - tower.playertarget->MapPosition.y, 2)) > tower.Range)
	{
		return new TowerIdleState();
	}
	return 0;
}
void TowerAttackingPlayerState::update(Tower& tower)
{
	extern SDL_Renderer* grender;
	if (tower.attackcounter >= 200)
	{
		tower.attackcounter = 0;
		//make sure our target is the same
		if (tower.playertarget == NULL)
		{
			cout << "attacking nothing" << endl;
		}
		else
		{
			if (tower.playertarget != NULL)
			{
				tower.playertarget->DamagePlayer(tower.damage);
			}
		}
	}

	if (tower.playertarget != 0)
	{
		if (tower.BotSide)
		{
			SDL_SetRenderDrawColor(grender, 0, 0, 255, 0);
			SDL_RenderDrawLine(grender, tower.Position.x + 35, tower.Position.y - 105, tower.playertarget->Position.x, tower.playertarget->Position.y);
		}
		else
		{
			SDL_SetRenderDrawColor(grender, 255, 0, 0, 0);
			SDL_RenderDrawLine(grender, tower.Position.x - 35, tower.Position.y - 105, tower.playertarget->Position.x, tower.playertarget->Position.y);
		}
	}
}