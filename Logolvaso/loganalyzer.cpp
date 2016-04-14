#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>

/*
car types:
0 : normal
1 : police
2 : gangster
3 : gangster (caught)
*/

struct CAR
{
	long int from;	//Start csomopont
	long int to;	//Cel csomopont
	long int step;
	int type;	//Car tipusa
	long int ido;	//Elfogas ideje
};

//Betolto-csik
void loading (double percent)
{
  int hatar = (int) (0.5 * percent);
  system("clear");
  std::cout << "Folyamatban...\n[" ;
  for (int i = 0; i < 50; i++)
  {
    if (i <= hatar)
    {
      std::cout << '=';
    }
    else 
    {
      std::cout << '-';
    }
  }
  std::cout << ']';
  std::cout << percent << "%\n";
}

int main(int argc, char const *argv[])
{
	//Ideiglenes tarolok
	long int temp_int;
	std::string temp_str;

	//Bemenet vizsgalata
	if (argc != 2)
	{
		std::cout << "\nHelytelen bemenet!\n./loganalizer <LOGFILE>\n\n";
		return 1;
	}

	//Sorszamlalo
	long int rows_sum = 0;
	long int rows_act = 0;
	std::ifstream counter (argv[1]);
	while (std::getline(counter, temp_str))
	{
		rows_sum++;
	}

	int oldpercent, percent = 0;
	std::ifstream logfile (argv[1]);
	int timestamp, minutes, num_cars;
	CAR gangsters_caught[1024];
	//Szamlalja, hogy hol jarunk a tombben
	int hanyadik_gangster_caught = 0;

	while (!logfile.eof())
	{
		logfile >> timestamp >> minutes >> num_cars;
		if (timestamp == (minutes*300))
		{
			break;
		}
		percent = ((double)rows_act / (double)rows_sum) * 100;
		//Szazalekonkent kirajzol
		if (oldpercent != percent)
		{
			loading(percent);
			//std::cout << timestamp << "|" << minutes << "|" << num_cars << "\t" << rows_act << " / " << rows_sum << " = " << percent << std::endl;
			oldpercent = percent;
		}
		rows_act++;
		CAR car;
		for (int i = 0; i < num_cars; ++i)
		{
			logfile >> car.from >> car.to >> temp_int >> car.step >> car.type;
			car.ido = timestamp;
			rows_act++;
			//Ha rendor, akkor meg tartozik hozza 2 elem, amiket le kell kezelnunk
			if (car.type == 1)
			{
				logfile >> temp_int >> temp_str;
			}
			//Ha elkapott-gengszter, és még nincs benne a tombben, akkor belerakja
			if (car.type == 3)
			{
				int talalt = 0;
				for (int j = 0; j < hanyadik_gangster_caught; ++j)
				{
					if ((gangsters_caught[j].from == car.from) && (gangsters_caught[j].to == car.to) && (gangsters_caught[j].step == car.step))
					{
						talalt = 1;
						break;
					}
				}
				if (!talalt)
				{
					gangsters_caught[hanyadik_gangster_caught] = car;
					hanyadik_gangster_caught++;
				}
			}
		}
	}
	//Ha befejezte a beolvasast, kiirja ez elkapasokat, valamint az osszesitest
	for (int i = 0; i < hanyadik_gangster_caught; ++i)
	{
		std::cout << i+1 << ". Elkapas!\tMikor: " << gangsters_caught[i].ido/5 << ". masodperc\tCsomopontok: " << gangsters_caught[i].from << " - " << gangsters_caught[i].to << std::endl;
	}
	std::cout << "\nOsszesen " << hanyadik_gangster_caught << " Gengsztert sikerult elkapni" << std::endl;
	return 0;
}