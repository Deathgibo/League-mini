#include "TowerIdleState.h"
#include "TowerAttackingMinionState.h"
#include "TowerAttackingPlayerState.h"

TowerIdleState::TowerIdleState()
{

}
TowerState* TowerIdleState::handleinput(Tower& tower)
{
	extern vector<Minion> minions;
	extern Player theplayer;

	bool enemyplayer = false;
	bool enemyminion = false;

	for (int i = 0; i < minions.size(); i++)
	{
		if (tower.BotSide != minions[i].BotSide)
		{
			if (sqrt(pow(tower.MapPosition.x - minions[i].MapPosition.x, 2) + pow(tower.MapPosition.y - minions[i].MapPosition.y, 2)) <= tower.Range)
			{
				tower.miniontarget = &minions[i];
				return new TowerAttackingMinionState();
			}
		}
	}
	if (tower.BotSide != theplayer.BotSide)
	{
		if (sqrt(pow(tower.MapPosition.x - theplayer.MapPosition.x, 2) + pow(tower.MapPosition.y - theplayer.MapPosition.y, 2)) <= tower.Range)
		{
			tower.playertarget = &theplayer;
			return new TowerAttackingPlayerState();
		}
	}
	return 0;
}
void TowerIdleState::update(Tower& tower)
{

}