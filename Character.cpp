#include "Character.h"
#include <stdlib.h>
#include <fstream>
#include <iostream>
vector <string> Character::names;
vector < vector <string> > Character::weapons;
vector < vector <string> > Character::races;
vector < vector <string> > Character::armors;

int roll(int x,int d)
{
	if(x>0)
		return (rand() % d + 1) + roll(x-1,d);
	return 0;	
}

void Character::init()
{
	ifstream fname("names.dat");
	copy(istream_iterator<string>(fname),
		istream_iterator<string>(),
		back_inserter(names));
	fname.close();


	ifstream fweapon("weapons.dat");
	char tempc;
	string temps="";
	vector <string> tempv;

	while(fweapon >> tempc)
	{
		if(tempc == ':')
		{	
			weapons.push_back(tempv);
			tempv.clear();
		}else
		if(tempc != ';')
		{
			temps += tempc;
		}else
		{
			tempv.push_back(temps);	
			temps ="";	
		}
	}
	fweapon.close();

	ifstream frace("races.dat");

	while(frace >> tempc)
	{
		if(tempc == ':')
		{	
			races.push_back(tempv);
			tempv.clear();
		}else
		if(tempc != ';')
		{
			temps += tempc;
		}else
		{
			tempv.push_back(temps);	
			temps ="";	
		}
	}
	frace.close();

	ifstream farmor("armors.dat");

	while(farmor >> tempc)
	{
		if(tempc == ':')
		{	
			armors.push_back(tempv);
			tempv.clear();
		}else
		if(tempc != ';')
		{
			temps += tempc;
		}else
		{
			tempv.push_back(temps);	
			temps ="";	
		}
	}
	farmor.close();
}


Character::Character()
{
	static int amountOfNames = (init(), names.size());
	static int amountOfWeapons = weapons.size();
	static int amountOfRaces = races.size();
	static int amountOfArmors = armors.size();
	_name = names[rand() % amountOfNames];
	_proficiency = 2;
	_str = roll(3,6);
	_dex = roll(3,6);
	_con = roll(3,6);
	_int = roll(3,6);
	_wis = roll(3,6);
	_cha = roll(3,6);
	_exp = rand()%300+100;
	_hp = baseHp = 10 + roll(lvl()-1,10)+conm(); 
	_initiative = 0;
	_target = 0;

	_weaponId = rand() % amountOfWeapons;
	_weaponName = weapons[_weaponId][0];
	_weaponAmountofDice = stoi(weapons[_weaponId][1]);
	_weaponDamageDice = stoi(weapons[_weaponId][2]); 	
	_criticalHit = 0;
	_criticalHitFlag = 0;

	_raceId = rand() % amountOfRaces;
	_raceName = races[_raceId][0];
	_raceStr = stoi(races[_raceId][1]);
	_raceDex = stoi(races[_raceId][2]);
	_raceCon = stoi(races[_raceId][3]);
	_raceInt = stoi(races[_raceId][4]);
	_raceWis = stoi(races[_raceId][5]);
	_raceCha = stoi(races[_raceId][6]); 

	_armorId = rand() % amountOfArmors;
	_armorName = armors[_armorId][0];
	_armorValue = stoi(armors[_armorId][1]);
	_armorDexMod = stoi(armors[_armorId][2]);
}

string Character::weaponName()
{
	return _weaponName;
}

int Character::attackRoll()
{
	int value = roll(1,20);
	if(value == 20)
	{
		_criticalHit=1;
		_criticalHitFlag=1;		
	}
	return value+strm()+_proficiency; 

}

int Character::damageRoll()
{
	int damage = 0;
	if(_criticalHit==0)
	{
		damage = roll(_weaponAmountofDice,_weaponDamageDice)+strm();
	}	
	else
	{
		damage = roll(_weaponAmountofDice,_weaponDamageDice)+roll(_weaponAmountofDice,_weaponDamageDice)+strm();
		_criticalHit = 0;
	}
	if(damage>0)
			return damage;
	return 0 ;
}

int Character::rollInitiative() 
{
	return _initiative = roll(1,20);
}

int Character::findTarget(vector <Character> turnorder)
{
	for(int i = 0; i < turnorder.size();i ++)
	{
		if(turnorder[i].team() != _team)
		{
			_target = i;
			return _target;
		}
	}
	return -1;
}

int Character::hurt(int attackroll, int damageroll)
{
	//if (dexm() > _armorDexMod) ? _armorDexMod : dexm()
	if(attackroll > _armorValue+((dexm() > _armorDexMod) ? _armorDexMod : dexm()))
	{
		_hp -= damageroll;
		return damageroll;
	}
	return 0;
}

bool Character::isAlive()
{
	if(_hp>0)
		return true;
	return false;
}

void Character::exp(int value)
{
	_exp+=value;
	//if(lvl()<(_exp+value)/100)
}

void Character::inviteToTeam(int value)
{
	_team =value;
}

string Character::description()
{
	return _name + " LVL: " + to_string(lvl()) + " HP: " + to_string(_hp) + " Race: "+ _raceName + " Class: Warrior Weapon: " + _weaponName + " Armor: " + _armorName +" STR: " + to_string(_str) + " DEX: " + to_string(_dex) + " CON: " + to_string(_con) + " INT: " + to_string(_int) + " WIS: " + to_string(_wis) + " CHA: " + to_string(_cha) ;
}

string Character::critical()
{
	if(_criticalHitFlag)
	{
		_criticalHitFlag=0;
		return "CRITICAL HIT! ";
	}
	return "";
}