#pragma once
#include "MinionState.h"

class Minionafkstate : public MinionState
{
public:
	Minionafkstate();
	MinionState* handleinput(Minion& minion);
	void update(Minion& minion);
private:

};
