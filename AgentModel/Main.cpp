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
#define COEFF_OF_INFESTATIONS 94
#define NUMBER_OF_SOCIAL_CONNECTIONS 31
#define DURATION 110
#define ISOLATION_INGEX 92
#define SELF_ISOLATION_INGEX 50
#define TEST_PROBABILITY 92
#define START_TESTS 8

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
	int confirmed = 0;
	vector<int> listOfInfected;
	vector<int> listOfDeaths;
	vector<int> listOfRecovered;
	vector<int> listofTests;
	vector<int> days;
	vector<int> confirmedTests;
	int nsc = NUMBER_OF_SOCIAL_CONNECTIONS;
	vector<int> realTests = { 2243,20146,6906,4427,26258,19868,20511,79635,20000,40000,69500,39103,64503,57398,61397,37122,114698,94498,88092,91631,94305,81246,66021,91978,95421,104606,113873,117921,103506,89285,109935,149077,150384,169500,156199,141735,119824,164459,194591,225499,221711,154481,203244,157114,173374,169461,184276,234496,226499,188300,168641,177154,205544,225846,242392,259748,230926,205302,225713,238217,266477,282473,267930,250458,249507,253808,266639,294899,310895,296352,278880,277929,282230,295061,323321,339317,324774,307302,306352,310652,323483,351743,367740,353196,335725,334774,339074,351905,380165,396162,337166,291238,233061,281203,311875,286889,305227,337008,289488,227998,289727,316737,282206,301296,317051,265937,202377,252934,288589,308901,320221,322640,261574,203122,258893,298871,311052,312362,314810,259874,197553,255205,296536,299744,309971,291668,239675,185604,242076,288204,303611,316551,315248,236640,171962,232028,283017,321216,303221,298676,246140,177027,244577,290538,304753,318491,312272,250660,184281,248709,291805,304832,224642,408813,247846,187814,245441,295122,327964,334435,340668,269532,204833,275612,307319,334220,336190,333571,270057,202577,328415,286135,337215,356371,355178,279476,218756,301699,324922,346318,361923,364722,282021,237622,291007,357868,374157,390796,379073,308339,255899,338987,384174,402045,423395,436558,358511,295649,371865,439097,507919,648370,476106,409960,172960,436976,478489,502363,523860,449699,374888,496688,512145,546615,564095,550313,476308,402592,506959,553308,582442,575250,587935,512224,412596,491447,570981,524304,550863,590350,526846,397225,512114,591767,636888,601803,627849,534895,438761,525227,577345,596766,588296,590770,520533,362717,452837,505780,543979,587707,545390,474843,333052,444170,493583,533761,550424,545261,448667,323453,427018,499126,543001,539674,535353,463556,336560,427678,497622,539303,527319,523097,437156,312930,393445,480151,516171,511153,494071,416572,292690,395008,445015,474243,386001,114290,114290,114290,217791,268620,630477,268668,342405,383652,326357,341381,465028,531024,583820,478817,373123,257909,320711,410533,456736,436520,441206,335236,292367,342015,397080,411272,423497,414747,333065,201301,287056,382721,458537,404247,396943,325972,214144,284417,355112,399477,393651,377905,299935,204488,277571,363166,374563,365425,368826,341426,225305,202632,162804,265528,364693,397611,314393,203520,285119,343927,362296,385253,354205,281959,184744,146308,249859,337250,382303,369224,290594,214523,274531,348715,364166,370769,352747,274025,183798,265176,334930,337695,341455,341365,267729,188733,284123,343403,359267,342237,365233,249433,194518,249683,323105,340527,344845,347655,272181,193375,255350,305799,377751,355627,337107,263903,184490,255962,314230,332888,336366,324879,262436,179796,251749,323761,328298,341716,324713,236109,153392,174309,221435,264152,277929,296159,258282,193338,210132,270613,369841,361657,374100,308461,213134,276580,337162,358989,334880,360270,289171,206525,271906,337866,375036,369782,382757,343516,271007,305567,351336,392952,381348,483099,188415,224825,305139,368732,400122,407065,420859,325738,253506,269402,351854,444649,473339,471432,383944,274606,436886,476324,505299,510187,501926,527202,248325,409908,479618,605300,567122,584184,488392,385879,473384,408026,561363,730274,594128,454631,352482,442858,601027,577794,598957,581203,461074,340694,435568,528489,551636,548829,550103,430477,323449,408286,535619,547469,527595,525109,441010,311521,389038,489658,536311,525289,512768,411367,304047,388663,482570,511000,496653,485847,404292,308047,381791,458440,494770,474528,478568,375579,294804,359415,567399,471144,463516,459418,386355,265404,352482,448836,464104,446097,434053,360110,255858,349884,422266,456421,464783,452462,357836,278335,353981,462467,517761,510253,485417,407223,295336,398693,499634,539792,527787,509798,418301,309514,505342,526116,579201,562211,557440,431581,344237,443250,550405,586978,584889,579127,484939,362154,468533,593210,608709,692106,659119,551796,408500,512218,624946,680879,963428,371247,594330,414771,557310,655856,701583,742692,689964,570109,435293,512837,571134,666254,524350,559187,453466,373771,495439,661784,714828,666772,631291,508081,370272,445050,561122,598106,572988,571601,452138,346979,416624,561715,607661,581760,560426,450838,369652,583249,655775,625403,611630,587654,485980,337482,446725,570848,629608,596993,562331,455518,325142,431654,535171,644784,546523,563840,459707,295658,415260,532831,521640,505670,480155,371919,306452,541758,457207,440961,575018 };
	

	//vector<int> tmp;
	//for (int i = 0; i < 200; i++)
	//{
	//	std::mt19937 socialGroup1(chrono::steady_clock::now().time_since_epoch().count());
	//	std::uniform_int_distribution<> makeselfisolation(0, 100);
	//	int selfisolateprob = makeselfisolation(socialGroup1);
	//	tmp.push_back(selfisolateprob);
	//}
	//int c = 0;
	//for (int i = 0; i < 200; i++)
	//{
	//	if (tmp[i] < 50) {
	//		c++;
	//	}
	//	//cout << tmp[i] << endl;
	//}
	//cout << "< 50: " << c << endl;
	for (int i = 0; i < DURATION; i++)
	{
		int testPerDay = 0;
		cout << "Day" << i << endl;
		if (i > 53) 
		{
			nsc = 24;
		}

		if (i > 69)
		{
			nsc = 18;
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
			std::mt19937 socialGroup1(chrono::steady_clock::now().time_since_epoch().count());
			std::uniform_int_distribution<> makeselfisolation(0, 1000);
			int selfisolateprob = makeselfisolation(socialGroup1);
			if (selfisolateprob < 2) // 2 скорее всего потому, что SetIsolation дает изоляцию на все время, а не на день. (Стоит переделать??)
			{
				a.SetIsolation();
			}
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
				if (a.GetStage() == 's' and !a.Isolation() and !a.IsTest())
				{
					if (i > START_TESTS)
					{
						std::uniform_int_distribution<> willmaketest(0, 100);
						int testprob = willmaketest(socialGroup);
						if (testprob <= TEST_PROBABILITY)
						{
							a.MakeTest();
							confirmed++;
							tests++;
							testPerDay++;

							if (a.IsInfected())
							{
								for (int j = num; j < num + 4; j++)
								{
									if (!agents[j].IsTest()) {
										agents[j].MakeTest();
										if (agents[j].IsInfected())
										{
											confirmed++;
										}
										tests++;
										testPerDay++;
									}
								}
							}
						}
					}
					
					//std::uniform_int_distribution<> selfIsolationIndex(0, 100);
					//int index = selfIsolationIndex(socialGroup);
					//if (index <= ISOLATION_INGEX)
					//{
					//	a.SetIsolation();
					//}
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
		int rIsolateCounter = 0;
		if (i >= 8 && testPerDay < floor(realTests[i - 8] / 9))
		{
			for (int j = 0; j < floor(realTests[i - 8]/9) - testPerDay; j++)
			{
				std::mt19937 socialGroup1(chrono::steady_clock::now().time_since_epoch().count());
				std::uniform_int_distribution<> randomtest(0, nubmerOfAgents);
				int rtest = randomtest(socialGroup1);
				std::uniform_int_distribution<> willmaketest(0, 100);
				int testprob = willmaketest(socialGroup1);
				if (testprob <= TEST_PROBABILITY)
				{
					agents[rtest].MakeTest();
					if (agents[rtest].IsInfected()) {
						confirmed++;
					}
					tests++;
					// Функция MakeTest работает таким образом, что изолирует каждого агента, для которого вызывается и следовательно мы не можем регулировать индекс изоляции

				}

				
				//std::uniform_int_distribution<> selfIsolationIndex(0, 100);
				//int index = selfIsolationIndex(socialGroup1);
				//if (index <= ISOLATION_INGEX)
				//{
				//	agents[rtest].SetIsolation();
				//	rIsolateCounter++;
				//}
			}

		}
		cout << "Изолировано в день " << i << " " << rIsolateCounter << "Человек" << endl;
		//cout << "Day " << i << endl;
		listOfInfected.push_back(counter);
		listOfDeaths.push_back(death);
		listOfRecovered.push_back(recovered);
		listofTests.push_back(tests);
		confirmedTests.push_back(confirmed);
		days.push_back(i);

	}
	cout << "Sick = " << counter << endl;
	cout << "Death = " << death << endl;
	cout << "Recovered = " << recovered << endl;
	cout << "Tests = " << tests << endl;
	cout << "Confirmed = " << confirmed << endl;
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
	f << endl;
	for (auto c : confirmedTests)
	{
		f << c << ",";
	}


	f.close();
	//system("pause");

}

int main() 
{
	const int nubmerOfAgents = 12000000;
	const int countOfPatientZero = 30;
	vector<Agent> agents = MakeAgentsVecor(nubmerOfAgents);
	for (int i = 0; i < countOfPatientZero; i++)
	{
		agents[ChoicePatientZero(countOfPatientZero, nubmerOfAgents)].Infection();
	}

	int counter = 0;
	SimulateInfection(agents, nubmerOfAgents);

} 