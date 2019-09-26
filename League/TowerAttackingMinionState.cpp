#include "TowerAttackingMinionState.h"
#include "TowerIdleState.h"

TowerAttackingMinionState::TowerAttackingMinionState()
{

}
TowerState* TowerAttackingMinionState::handleinput(Tower& tower)
{
	if (tower.miniontarget == NULL || tower.miniontarget->currenthealth <= 0)
	{
		return new TowerIdleState();
	}
	/*if minion is out of range*/
	if (sqrt(pow(tower.MapPosition.x - tower.miniontarget->MapPosition.x, 2) + pow(tower.MapPosition.y - tower.miniontarget->MapPosition.y, 2)) > tower.Range)
	{
		return new TowerIdleState();
	}
	return 0;
}
void TowerAttackingMinionState::update(Tower& tower)
{
	extern SDL_Renderer* grender;
	if (tower.attackcounter >= 200)
	{
		tower.attackcounter = 0;
		//make sure our target is the same
		if (tower.miniontarget == NULL)
		{
			cout << "attacking nothing" << endl;
		}
		else
		{
			if (tower.miniontarget != NULL)
			{
				tower.miniontarget->DamageMinion(tower.damage);
			}
		}
	}

	if (tower.miniontarget != 0)
	{
		if (tower.BotSide)
		{
			SDL_SetRenderDrawColor(grender, 0, 0, 255, 0);
			SDL_RenderDrawLine(grender, tower.Position.x + 35, tower.Position.y - 105, tower.miniontarget->Position.x, tower.miniontarget->Position.y);
		}
		else
		{
			SDL_SetRenderDrawColor(grender, 255, 0, 0, 0);
			SDL_RenderDrawLine(grender, tower.Position.x - 35, tower.Position.y - 105, tower.miniontarget->Position.x, tower.miniontarget->Position.y);
		}
	}
}