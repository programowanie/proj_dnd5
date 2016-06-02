#include "Character.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream> 
#include <algorithm>

#define TIMER 1000000

bool sortByInitiative( Character &lhs,  Character &rhs) { return lhs.initiative() > rhs.initiative(); }

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	//ver 0.02
	int N = 2; //liczba postaci
	int M = 5; //liczba druzyn
	Character character[M][N];

	vector <Character> turnorder;

	for(int j = 0; j < M; j++)
	{

		cout << "Team " << j <<":"<<endl;
		usleep(TIMER *2);
		for(int i = 0; i < N; i++)
		{
			cout << character[j][i].description()<<endl;
			character[j][i].inviteToTeam(j);
			character[j][i].rollInitiative();
			turnorder.push_back(character[j][i]);
		}
		if(j!=M-1 ) cout << "VS"<<endl;
	}
	cout << endl;
	sort(turnorder.begin(), turnorder.end(), sortByInitiative);
	// wypisanie turn order
	cout << "Turn order:"<<endl;
	for(int i = 0; i < N*M; i++)
	{
		//turnorder[i].initiative()
		cout << i+1  << ". Name: " << turnorder[i].name() << " Team: " << turnorder[i].team() << endl;
	
	}
	cout << endl;
	
	bool fight = 1;
	int winner = 0;
	while(fight)
	{
		
		for(int i=0; i < turnorder.size(); i++)
		{
			usleep(TIMER);
			int target = turnorder[i].findTarget(turnorder);
			if(target ==-1 )
			{
				winner = turnorder[i].team();
				fight = 0;
			}else
			{
				int attackroll = turnorder[i].attackRoll();
				int damageroll = turnorder[i].damageRoll();
				int hurt =  turnorder[target].hurt(attackroll,damageroll);
				if(hurt)
				{
					//<< attackroll << "|" << damageroll << "] "<<
					cout << turnorder[i].name() <<" is attacking "<< turnorder[target].name()<<" with "<< turnorder[i].weaponName() << " dealing "<< hurt << " damage. " << turnorder[i]. critical()<<endl;
					if (!turnorder[target].isAlive())
					{
						cout << turnorder[target].name() << " dies." <<endl;
						turnorder.erase(turnorder.begin()+target);
					} 
				}else
				{
					cout << turnorder[i].name() <<" is attacking "<< turnorder[target].name()<<" with "<< turnorder[i].weaponName() << " but misses." <<endl;
				}
			}
		}
	}
	cout << "Winner is Team " << winner <<endl;
	for(int i = 0; i < turnorder.size(); i++)
	{
		cout << turnorder[i].description()<<endl;
		turnorder[i].exp(100);
	}	
}