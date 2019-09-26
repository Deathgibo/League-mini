#include "MinionKnockupState.h"
#include "MinionWalkingState.h"


MinionKnockupState::MinionKnockupState(int theduration)
{
	duration = theduration;
	up = true;
	framecounter = 0;
}
MinionState* MinionKnockupState::handleinput(Minion& minion)
{
	if (done)
	{
		return new MinionWalkingState();
	}
	return 0;
}
void MinionKnockupState::update(Minion& minion)
{
	if (!done)
	{
		if (up)
		{
			minion.MapPosition.y--;
			framecounter++;
			if (framecounter > duration/2)
			{
				up = false;
				framecounter = 0;
			}
		}
		else
		{
			minion.MapPosition.y++;
			framecounter++;
			if (framecounter > duration / 2)
			{
				done = true;
				framecounter = 0;
			}
		}
	}
}