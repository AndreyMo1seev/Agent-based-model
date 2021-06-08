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
#include <fstream>
//#include "../matplotlib-cpp-master/matplotlibcpp.h"
#define COEFF_OF_INFESTATIONS 103
#define NUMBER_OF_SOCIAL_CONNECTIONS 31
#define DURATION 90
#define SELF_ISOLATION_INGEX 92
#define TEST_PROBABILITY 95
#define START_TESTS 25

using namespace std;
//namespace plt = matplotlibcpp;

class Agent
{
private:
	int age;
	int dayOfDayIllness;
	bool infected;
	bool death;
	bool self_isolation;
	bool test;
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
	bool IsRecovered()
	{
		if (stage == 'r')
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool IsTest()
	{
		return test;
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
	void SetIsolation()
	{
		self_isolation = true;
	}
	void MakeTest()
	{
		test = true;
		if (infected == true)
		{
			self_isolation = true;
		}
	}
	bool Isolation()
	{
		return self_isolation;
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
		if (dayOfDayIllness > 3)
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
		std::uniform_int_distribution<> deathProbability(0, 34000);
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
		std::mt19937 ageDistribution(chrono::steady_clock::now().time_since_epoch().count());
		std::uniform_int_distribution<> ageProbability(0, 10000);
		int probabilityValue = ageProbability(ageDistribution);
		//age = uid(gend);
		if (probabilityValue <= 1219)
		{
			std::uniform_int_distribution<> uid3(0, 9);
			age = uid3(gend);
		}
		if (1219 < probabilityValue <= 3367)
		{
			std::uniform_int_distribution<> uid3(10, 29);
			age = uid3(gend);
		}
		if (3367 < probabilityValue <= 5046)
		{
			std::uniform_int_distribution<> uid3(30, 39);
			age = uid3(gend);
		}
		if (5046 < probabilityValue <= 6450)
		{
			std::uniform_int_distribution<> uid3(40, 49);
			age = uid3(gend);
		}
		if (6450 < probabilityValue <= 7764)
		{
			std::uniform_int_distribution<> uid3(50, 59);
			age = uid3(gend);
		}
		if (7764 < probabilityValue <= 9021)
		{
			std::uniform_int_distribution<> uid3(60, 69);
			age = uid3(gend);
		}
		if (9021 < probabilityValue <= 9613)
		{
			std::uniform_int_distribution<> uid3(70, 79);
			age = uid3(gend);
		}
		if (9613 < probabilityValue <= 10000)
		{
			std::uniform_int_distribution<> uid3(80, 95);
			age = uid3(gend);
		}
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
		self_isolation = false;
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
	int recovered = 0;
	int tests = 0;
	vector<int> listOfInfected;
	vector<int> listOfDeaths;
	vector<int> listOfRecovered;
	vector<int> listofTests;
	vector<int> days;
	int nsc = NUMBER_OF_SOCIAL_CONNECTIONS;
	
	for (int i = 0; i < DURATION; i++)
	{
		cout << "Day" << i << endl;
		if (i > 55) 
		{
			nsc = 26;
		}
		else
		{
			if (i > 80)
			{
				nsc = 24;
			}

		}

		for (auto& a : agents)
		{
			if (a.IsDeath()) {
				continue;
			}

			if (a.IsRecovered())
			{
				recovered++;
			}
			/*
			if (a.IsTest())
			{
				tests++;
			}
			*/
			if (a.IsInfected())
			{
				std::mt19937 socialGroup(chrono::steady_clock::now().time_since_epoch().count());
				std::uniform_int_distribution<> socialGroupRange(0, nsc);
				std::uniform_int_distribution<> position(0, nubmerOfAgents - nsc);
				int socialNumber = socialGroupRange(socialGroup);
				int num = position(socialGroup);
				a.IncrementDayOfDayIllness();
				a.ControlStage();
				if (!a.Isolation()) {
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
				}
				if (a.GetStage() == 's' and !a.Isolation())
				{
					if (i > START_TESTS)
					{
						std::uniform_int_distribution<> willmaketest(0, 100);
						int testprob = willmaketest(socialGroup);
						if (testprob <= TEST_PROBABILITY)
						{
							a.MakeTest();
							tests++;
							if (a.IsInfected())
							{
								for (int j = num; j < num + 4; j++)
								{
									agents[j].MakeTest();
									tests++;
								}
							}
						}
					}
					
					std::uniform_int_distribution<> selfIsolationIndex(0, 100);
					int index = selfIsolationIndex(socialGroup);
					if (index <= SELF_ISOLATION_INGEX)
					{
						a.SetIsolation();
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
				/*
				if (a.GetStage() == 'r')
				{
					recovered++;
				}
				*/
			}
		}
		//cout << "Day " << i << endl;
		listOfInfected.push_back(counter);
		listOfDeaths.push_back(death);
		listOfRecovered.push_back(recovered);
		listofTests.push_back(tests);
		days.push_back(i);

	}
	cout << "Sick = " << counter << endl;
	cout << "Death = " << death << endl;
	cout << "Recovered = " << recovered << endl;
	cout << "Tests = " << tests << endl;
	//cout << "Data for indection plot"<< endl;
	/*
	for (auto c : days)
	{
		cout << c << ",";
	}
	cout << endl;
	for (auto c : listOfInfected)
	{
		cout << c << ",";
	}
	cout << endl;

	cout << "Data for death plot"<< endl;
	for (auto c : days)
	{
		cout << c << ",";
	}
	cout << endl;
	for (auto c : listOfDeaths)
	{
		cout << c << ",";
	}
	cout << endl;

	cout << "Data for recovered plot" << endl;
	for (auto c : days)
	{
		cout << c << ",";
	}
	cout << endl;
	for (auto c : listOfRecovered)
	{
		cout << c << ",";
	}
	cout << endl;
	*/
	ofstream f;
	f.open("data.csv");

	vector<int> realData = {55,86,98,131,137,191,262,290,410,546,703,817,1014,1226,1613,1880,2475,2923,3357,3893,4484,5181,5841,6698,7822,8852,10158,11513,13002,14776,16146,18105,20754,24324,26350,29433,31981,33940,36897,39509,45351,48426,50646,53739,57300,62658,68606,74401,80115,85973,92676,98522,104189,109740,115909,121301,126004,130716,135464,138969,142824,146062,149607,152306,155219,158207,161397,163913,166473,169303,171443,173497,175829,178196,180791,183088,185374,187216,189214,191069,193061,195017,197018,198590,199785,201221,202935,204428,205905,207264 };

	for (auto c : days)
	{
		f << c << ",";
	}
	f << endl;
	for (auto c : days)
	{
		f << c << ",";
	}
	f << endl;
	for (auto c : listOfInfected)
	{
		f << c << ",";
	}
	f << endl;
	for (auto c : realData)
	{
		f << c << ",";
	}
	f << endl;
	for (auto c : listOfDeaths)
	{
		f << c << ",";
	}
	f << endl;
	for (auto c : listOfRecovered)
	{
		f << c << ",";
	}


	f.close();
	//system("pause");

}

int main() 
{
	const int nubmerOfAgents = 12000000;
	const int countOfPatientZero = 190;
	vector<Agent> agents = MakeAgentsVecor(nubmerOfAgents);
	for (int i = 0; i < countOfPatientZero; i++)
	{
		agents[ChoicePatientZero(countOfPatientZero, nubmerOfAgents)].Infection();
	}

	int counter = 0;
	SimulateInfection(agents, nubmerOfAgents);

} 