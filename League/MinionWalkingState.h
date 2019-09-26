#pragma once
#include "MinionState.h"


class AttackingMinionState;

class MinionWalkingState : public MinionState
{
public:
	MinionWalkingState();
	MinionState* handleinput(Minion& minion);
	void update(Minion& minion);

private:

};
