#include "AttackingPlayerState.h"
#include "MinionWalkingState.h"
#include "MinionWalkToLaneState.h"
#include "Tower.h"

AttackingPlayerState::AttackingPlayerState()
{
}
MinionState* AttackingPlayerState::handleinput(Minion& minion)
{
	/*if player is killed go back to walking*/
	if (minion.playertarget == NULL || minion.playertarget->currenthealth <= 0)
	{
		minion.playertarget = 0;
		return new MinionWalkingState();
	}

	/*if minion is outside lane limit go to walkback state*/
	if (!IsMinionWithinLane(minion,minion.chasingrangelimit))
	{
		minion.playertarget = 0;
		return new MinionWalkToLaneState();
	}

	/*if player walks out of attack range go back to walking*/
	if (sqrt(pow(minion.MapPosition.x - minion.playertarget->MapPosition.x, 2) + pow(minion.MapPosition.y - minion.playertarget->MapPosition.y, 2)) > minion.AttackRange)
	{
		minion.playertarget = 0;
		return new MinionWalkingState();
	}
	return 0;
}
void AttackingPlayerState::update(Minion& minion)
{
	extern SDL_Renderer* grender;

	if (minion.attackcounter >= 200)
	{
		minion.attackcounter = 0;
		if (minion.playertarget == NULL)
		{
			cout << "minion not attacking a player" << endl;
		}
		else
		{
			if (minion.playertarget != NULL)
			{
				minion.playertarget->DamagePlayer(minion.damage);
			}
		}
	}
}