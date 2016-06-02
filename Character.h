#pragma once

#include <string>
#include <vector>
#include <iterator>

using namespace std;



class Character
{
	static vector <string> names;
	static vector < vector <string> > weapons;
	static vector < vector <string> > races;
	static vector < vector <string> > armors;
	string _name;
	int _team, _target;
	int _hp, baseHp; 
	int _str, _dex, _con, _int, _wis, _cha;
	int _proficiency;
	int _exp, _initiative;
	int _class,_race;

	int _weaponId;
	string _weaponName;
	int _weaponAmountofDice;
	int _weaponDamageDice; 
	bool _criticalHit;
	bool _criticalHitFlag;

	int _raceId;
	string _raceName;
	int _raceStr,_raceDex,_raceCon,_raceInt,_raceWis,_raceCha;

	int _armorId;
	string _armorName;
	int _armorValue;
	int _armorDexMod;

	static void init();

public:
	Character();
//	~Character();

	int hp() { return _hp; }
	string name() { return _name; }
	int team() { return _team; }
	int target() { return _target; }
	int strm() { return _str/2 -5; }
	int dexm() { return _dex/2 -5; }
	int conm() { return _con/2 -5; }
	int intm() { return _int/2 -5; }
	int wism() { return _wis/2 -5; }
	int cham() { return _cha/2 -5; }
	int initiative() { return _initiative; }
	int lvl() {return _exp/100; }

	
	int rollInitiative();
	int findTarget(vector <Character>);
	int attackRoll();
	int damageRoll();
	int hurt(int,int);

	bool isAlive();

	void exp(int);
	
	void inviteToTeam(int);

	string weaponName();
	string description();
	string critical();
};
