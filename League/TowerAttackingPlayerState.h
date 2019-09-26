#pragma once
#include "TowerState.h"

class TowerAttackingPlayerState : public TowerState
{
public:
	TowerAttackingPlayerState();
	TowerState* handleinput(Tower& tower);//handles the input for the other states that state can go to
	void update(Tower& tower);

private:


};