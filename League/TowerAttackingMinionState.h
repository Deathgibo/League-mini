#pragma once
#include "TowerState.h"

class TowerAttackingMinionState : public TowerState
{
public:
	TowerAttackingMinionState();
	TowerState* handleinput(Tower& tower);//handles the input for the other states that state can go to
	void update(Tower& tower);

private:


};