#include "AttackingTowerState.h"
#include "MinionWalkingState.h"
#include "Tower.h"

AttackingTowerState::AttackingTowerState()
{
}
MinionState* AttackingTowerState::handleinput(Minion& minion)
{
	//if targeted minion is not there anymore return to walking
	if (minion.towertarget == NULL || minion.towertarget->currenthealth <= 0 || minion.towertarget->alive == false)
	{
		return new MinionWalkingState();
	}
	return 0;
}
void AttackingTowerState::update(Minion& minion)
{
	extern SDL_Renderer* grender;

	if (minion.attackcounter >= 200)
	{
		minion.attackcounter = 0;
		if (minion.towertarget == NULL)
		{
			cout << "minion not attacking a tower" << endl;
		}
		else
		{
			if (minion.towertarget != NULL)
			{
				minion.towertarget->DamageTower(minion.damage);
			}
		}
	}
}