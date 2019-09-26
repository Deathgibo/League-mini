#include "AttackingMinionState.h"
#include "MinionWalkingState.h"
#include "MinionWalkToLaneState.h"

AttackingMinionState::AttackingMinionState()
{
}
MinionState* AttackingMinionState::handleinput(Minion& minion)
{
	/*if targeted minion is killed go back to walking*/
	if (minion.miniontarget == NULL || minion.miniontarget->currenthealth <= 0)
	{
		minion.miniontarget = 0;
		return new MinionWalkingState();
	}

	/*if minion is outside lane limit go to walkback state*/
	if (!IsMinionWithinLane(minion, minion.chasingrangelimit))
	{
		minion.miniontarget = 0;
		return new MinionWalkToLaneState();
	}

	/*if minion leaves attack range go back to walking*/
	if (sqrt(pow(minion.MapPosition.x - minion.miniontarget->MapPosition.x, 2) + pow(minion.MapPosition.y - minion.miniontarget->MapPosition.y, 2)) > minion.AttackRange)
	{
		minion.miniontarget = 0;
		return new MinionWalkingState();
	}
	return 0;
}
void AttackingMinionState::update(Minion& minion)
{
	extern SDL_Renderer* grender;
	if (minion.attackcounter >= 200)
	{
		minion.attackcounter = 0;
		if (minion.miniontarget == NULL)
		{
			cout << "minion not attacking minion" << endl;
		}
		else
		{
			if (minion.miniontarget != NULL)
			{
				minion.miniontarget->DamageMinion(minion.damage);
			}
		}
	}

	/*if (minion.miniontarget != 0)
	{
		if (minion.BotSide)
		{
			SDL_SetRenderDrawColor(grender, 0, 0, 255, 0);
		}
		else
		{
			SDL_SetRenderDrawColor(grender, 255, 0, 0, 0);
			//SDL_RenderDrawLine(grender, minion.Position.x, minion.Position.y, minion.miniontarget->Position.x, minion.miniontarget->Position.y);
		}
		//SDL_RenderDrawLine(grender, minion.Position.x, minion.Position.y, minion.miniontarget->Position.x, minion.miniontarget->Position.y);
	}
	//damage targeted minions health every x seconds*/
}