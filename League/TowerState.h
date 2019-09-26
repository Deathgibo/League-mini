#pragma once
#include "Tower.h"
#include <iostream>
using namespace std;

class TowerState
{
public:
	virtual ~TowerState()
	{

	}
	virtual TowerState* handleinput(Tower& tower)//handles the input for the other states that state can go to
	{
		return 0;
	}
	virtual void update(Tower& tower)
	{

	}
protected:


private:

};