#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <cctype>
#include <random>
#include <time.h>
#include <chrono>
#define COEFF_OF_INFESTATIONS 190
#define NUMBER_OF_SOCIAL_CONNECTIONS 20
#define DURATION 60

using namespace std;
/*
bool operator!= (Agent() ag1, Agent() ag2)
{
	if (ag1.GetAge() != ag2.GetAge() && ag1.GetDayOfDayIllness() != ag2.GetDayOfDayIllness() && ag1.GetStage() != ag2.GetStage() && ag1.GetGender() != ag2.GetGender())
	{
		return true;
	}
	else
	{
		return false;
	}
}
*/
class Agent
{
private:
	int age;
	int dayOfDayIllness;
	bool infected;
	bool death;
	char stage;
	char gender;

public:
	void SetAge(const int  _age)
	{
		age = _age;
	}
	void Infection()
	{
		infected = true;
		dayOfDayIllness++;
		stage = 'w';
	}
	void SetGender(const char _gender)
	{
		gender = _gender;
	}
	void IncrementDayOfDayIllness()
	{
		dayOfDayIllness++;
	}
	bool IsInfected()
	{
		return infected;
	}
	int GetAge()
	{
		return age;
	}
	char GetGender()
	{
		return gender;
	}
	char GetStage()
	{
		return stage;
	}
	int GetDayOfDayIllness()
	{
		return dayOfDayIllness;
	}
	void Death()
	{
		death = true;
	}
	bool IsDeath()
	{
		return death;
	}
	
	bool operator!= (Agent ag)
	{
		if (this->age != ag.age || this->dayOfDayIllness != ag.dayOfDayIllness || this->stage != ag.stage || this->gender != ag.gender)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	void ControlStage()
	{
		//Для начала примем, что все проходят одни и те же стадии и они длятся одно и то же время 
		if (dayOfDayIllness > 5)
		{
			stage = 's';
		}
		if (dayOfDayIllness > 10)
		{
			stage = 't';
		}
		if (dayOfDayIllness > 20) {
			stage = 'r';
			infected = false;
			dayOfDayIllness = -1;
		}
	}
	vector<Agent> Del(vector<Agent> agents)
	{
		vector<Agent> new_agents;
		for (auto ag : agents)
		{
			if (ag != *this)
			{
				new_agents.push_back(ag);
			}
		}
		return new_agents;
	}
	bool TryToDie()
	{
		// предполагаем, что человек может умереть только на второй стадии болезни (t) и то, что эта 
		// фаза длится примерно 10 дней. Вероятности умереть в каждый день стадии (t) равны
		std::mt19937 death(chrono::steady_clock::now().time_since_epoch().count());
		std::uniform_int_distribution<> deathProbability(0, 1000);
		int probabilityValue = deathProbability(death);
		if (age <= 10)
		{
			return false;
		}
		if (age > 10 && age <= 30 && probabilityValue < 2)
		{
			return true;
		}
		if (age > 30 && age <= 40 && probabilityValue < 3)
		{
			return true;
		}
		if (age > 40 && age <= 50 && probabilityValue < 4)
		{
			return true;
		}
		if (age > 50 && age <= 60 && probabilityValue < 13)
		{
			return true;
		}
		if (age > 60 && age <= 70 && probabilityValue < 36)
		{
			return true;
		}
		if (age > 70 && age <= 80 && probabilityValue < 80)
		{
			return true;
		}
		if (age > 80 && probabilityValue < 148)
		{
			return true;
		}
		return false;
	}
	Agent()
	{
		std::mt19937 gend(chrono::steady_clock::now().time_since_epoch().count());
		std::uniform_int_distribution<> uid(1, 90);
		std::uniform_int_distribution<> uid2(0, 1);
		age = uid(gend);
		int tmp = uid2(gend);
			if (tmp == 0)
			{
				gender = 'm';
			}
			else
			{
				gender = 'f';
			}
		infected = false;
		stage = 'n';
		dayOfDayIllness = -1;
		death = false;
	}
	~Agent()
	{

	}
};

vector<Agent> MakeAgentsVecor(const int nubmerOfAgents)
{
	vector<Agent> agents;
	for (int i = 0; i < nubmerOfAgents; i++)
	{
		agents.push_back(Agent());
	}
	return agents;
}
/*
bool operator!= (Agent ag1, Agent ag2)
{
	if (ag1.GetAge() != ag2.GetAge() && ag1.GetDayOfDayIllness() != ag2.GetDayOfDayIllness() && ag1.GetStage() != ag2.GetStage() && ag1.GetGender() != ag2.GetGender())
	{
		return true;
	}
	else
	{
		return false;
	}
}
*/
int ChoicePatientZero(const int countOfPatientZero, const int nubmerOfAgents)
{
	std::mt19937 patient(chrono::steady_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<> patientRange(0, nubmerOfAgents - 1);
	return patientRange(patient);
}

bool ContactInfectionProbability()
{
	std::mt19937 infect(chrono::steady_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<> coeff(0, COEFF_OF_INFESTATIONS);
	int ver = coeff(infect);
	if (ver >= COEFF_OF_INFESTATIONS - 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void SimulateInfection(vector<Agent> agents, const int nubmerOfAgents)
{
	int counter = 1;
	int death = 0;
	for (int i = 0; i < DURATION; i++)
	{
		for (auto& a : agents)
		{
			if (a.IsDeath()) {
				continue;
			}
			
			if (a.IsInfected())
			{
				std::mt19937 socialGroup(chrono::steady_clock::now().time_since_epoch().count());
				std::uniform_int_distribution<> socialGroupRange(0, NUMBER_OF_SOCIAL_CONNECTIONS);
				std::uniform_int_distribution<> position(0, nubmerOfAgents - NUMBER_OF_SOCIAL_CONNECTIONS);
				int socialNumber = socialGroupRange(socialGroup);
				int num = position(socialGroup);
				a.IncrementDayOfDayIllness();
				a.ControlStage();
				for (int i = num; i < num + socialNumber; i++)
				{
					if (!agents[i].IsInfected())
					{

						if (ContactInfectionProbability())
						{
							agents[i].Infection();
							counter++;
						}
					}
				}
				if (a.GetStage() == 't')
				{
					a.ControlStage();
				}
				if (a.GetStage() == 't' && a.TryToDie())
				{
					//agents.erase(std::remove(agents.begin(), agents.end(), a), agents.end());
					//delete &a;
					//agents = a.Del(agents);
					a.Death();
					death++;
				}
			}
		}
		//cout << "Day " << i << endl;

	}
	cout << "Sick = " << counter << endl;
	cout << "Death = " << death << endl;
	//system("pause");

}

int main() 
{
	const int nubmerOfAgents = 100000;
	const int countOfPatientZero = 10;
	vector<Agent> agents = MakeAgentsVecor(nubmerOfAgents);
	for (int i = 0; i < countOfPatientZero; i++)
	{
		agents[ChoicePatientZero(countOfPatientZero, nubmerOfAgents)].Infection();
	}

	int counter = 0;
	SimulateInfection(agents, nubmerOfAgents);

} 