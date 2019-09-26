#pragma once
#include "MinionState.h"

class AttackingPlayerState : public MinionState
{
public:
	AttackingPlayerState();
	MinionState* handleinput(Minion& minion);
	void update(Minion& minion);
private:

};