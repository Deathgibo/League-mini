#pragma once
#include "MinionState.h"


class MinionWalkToLaneState : public MinionState
{
public:
	MinionWalkToLaneState();
	MinionState* handleinput(Minion& minion);
	void update(Minion& minion);

private:

};

