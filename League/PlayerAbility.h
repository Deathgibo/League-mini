#pragma once
#include <iostream>
#include "Vertex.h"
#include <SDL.h>
#include "Player.h"
#include <string>
using namespace std;
class PlayerAbility
{
public:
	PlayerAbility(Player* player);
	virtual ~PlayerAbility();
	void activateabilities(Player* player);
	void AutoAttack(Player* player);

	/* description strings */
	string qname;
	int qmana;
	vector<string> qstring;

	string wname;
	int wmana;
	vector<string> wstring;

	string ename;
	int emana;
	vector<string> estring;

	string rname;
	int rmana;
	vector<string> rstring;

	string pname;
	int pmana;
	vector<string> pstring;

private:
	bool autoselected = false;
	bool automoving = false;
	bool autoing = false;
	bool chasingminion = false;
	bool chasingtower = false;
protected:
	Player* theplayer;
	bool justautod = false;
	bool ractivated = false;
	bool eactivate = false;
	bool pactivated = false;
	bool wactivated = false;
	bool qactivated = false;
	bool quickcasted = true;
	bool showquickcast = false;

	virtual void activate(Player* player) = 0;
	virtual void SetStrings();
	void showline(int radius);
	void showcircle();
	void move();
	void playersound();
	double getplayerx();
	double getplayery();
	Vertex getplayermiddle();

};