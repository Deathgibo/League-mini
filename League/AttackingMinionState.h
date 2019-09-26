#pragma once
#include "MinionState.h"
#ifndef MINIONWALKINGSTATE_H
#define MINIONWALKINGSTATE_H

class AttackingMinionState : public MinionState
{
public:
	AttackingMinionState();
	MinionState* handleinput(Minion& minion);
	void update(Minion& minion);
private:

};

#endif