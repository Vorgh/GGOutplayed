#include <iostream>
#include <string>
#include <fstream>
#include <vector>

//using namespace std;

int main( int argc, const char* argv[] )
{
   bool firstread = true;
   int number;
   double time = 0;
   long int from,to,tmp;
   int tick,type,cght;
   std::string s;
   int copcounter = 0;
   int copnumber;
   
   std::ifstream cops (argv[1]);
   while(!cops.eof())
   {
     bool stop = false;
     copcounter = 0;
     cops >> tmp >> tmp >> number;
     
     for (int i=0;i<number;i++)
     {
       cops >> tmp >> tmp >> tmp >> tmp >> type;
       if (type == 1)
       {
	 copcounter++;
	 stop = true;
	 cops >> tmp >> s;
       }
     }
     if (stop)
     {
       copnumber = copcounter;
       break;
     }
   }
   cops.close();
   
   int caught[copcounter];
   for (int i = 0; i < copcounter; i++)
   {
     caught[i] = 0;
   }
   std::ifstream olvaso (argv[1]);
   std::ofstream iro ("Rendornaplo.txt");
   while (!olvaso.eof())
   {
     copcounter = 0;
     olvaso >> tick >> tmp >> number;
     time += 0.2;
     for (int i=0;i<number;i++)
     {
       olvaso >> from >> to >> tmp >> tmp >> type;
       if (type == 1)
       {
	 olvaso >> cght >> s;
	 if(caught[copcounter] < cght)
	 {
	   caught[copcounter] = cght;
	   iro << to << "-nél elkaptam egy gangstert " << time << "-kor\n";
	 }
	 copcounter++;
       }
       if (copcounter > copnumber)
	 break;
     }
     if (tick == 3000)
       break;
   }
   olvaso.close();
   iro.close();
   return 0;
   
}