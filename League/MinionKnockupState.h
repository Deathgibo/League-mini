#pragma once
#include "MinionState.h"
#include "Vertex.h"

class MinionKnockupState : public MinionState
{
public:
	MinionKnockupState(int duration);
	MinionState* handleinput(Minion& minion);
	void update(Minion& minion);
private:
	bool done = false;
	bool up = true;
	int framecounter = 0;
	int duration;
};

