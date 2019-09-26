#pragma once
#include "MinionState.h"

class AttackingTowerState : public MinionState
{
public:
	AttackingTowerState();
	MinionState* handleinput(Minion& minion);
	void update(Minion& minion);
private:

};