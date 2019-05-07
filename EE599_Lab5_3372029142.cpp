#include <iostream>
#include <fstream>
#include <math.h>


using namespace std;

class City
{
public:
    int CityName;
    int X;
    int Y;

};

class SimulatedAnnealing
{
public:

    void swap(City *city,int n)
    {
        City middle;
        int c1 = rand()%n;
        int c2 = rand()%n;

        middle.CityName = city[c1].CityName;
        middle.X = city[c1].X;
        middle.Y = city[c1].Y;
        city[c1].CityName = city[c2].CityName;
        city[c1].X = city[c2].X;
        city[c1].Y = city[c2].Y;
        city[c2].CityName = middle.CityName;
        city[c2].X = middle.X;
        city[c2].Y = middle.Y;

    }

    int Annealing(City *city, int *rt, int n)
    {
        int i,j;
        double tp = 100;
        double tpmin = exp(-6);///
        double bt = 0.95;
        double zt;
        double k;
        int num_max = 50000;
        int num = 0;
        double rult = 0;
        double s= 0;
        double rn;

        for( i = 0; i < n-1; i++)
        {
            rult = rult + sqrt(pow(city[i+1].X-city[i].X,2)+pow(city[i+1].Y-city[i].Y,2));
        }
        rult = rult + sqrt(pow(city[0].X-city[n-1].X,2)+pow(city[0].Y-city[n-1].Y,2));

        while( num< num_max &&tp > tpmin)
        {
            swap(city, n);
            for(  j= 0;  j< n-1; j++)
            {
                s = s + sqrt(pow(city[j+1].X-city[j].X,2)+pow(city[j+1].Y-city[j].Y,2));
            }
            s = s + sqrt(pow(city[0].X-city[n-1].X,2)+pow(city[0].Y-city[n-1].Y,2));
            zt = (s - rult)/rult;

            if(zt<=0)
                k = 1;
            else
                k = exp(zt*(-1)/tp);
            rn = rand()/double(RAND_MAX);
            if(k>rn)
            {
                for(int i = 0; i < n; i++)
                {
                   rt[i] = city[i].CityName;
                }
                rt[n] = rt[0];
                tp = tp*bt;
                num = 0;
                rult = s;
            }
            else
            {
                num++;
            }
        }
        return rult;
    }
};


class Greedy
{
public:

    void swap(City *city,int n)
    {
        City middle;
        int c1 = rand()%n;
        int c2 = rand()%n;

        middle.CityName = city[c1].CityName;
        middle.X = city[c1].X;
        middle.Y = city[c1].Y;
        city[c1].CityName = city[c2].CityName;
        city[c1].X = city[c2].X;
        city[c1].Y = city[c2].Y;
        city[c2].CityName = middle.CityName;
        city[c2].X = middle.X;
        city[c2].Y = middle.Y;

    }

    int GreedyM(City *city, int *rt, int n)
    {
        int i,j;
        double rult= 0;
        double s=0;
        int num_max = 5000;
        for( i = 0; i < n-1; i++)
        {
            rult = rult + sqrt(pow(city[i+1].X-city[i].X,2)+pow(city[i+1].Y-city[i].Y,2));
        }
        rult = rult + sqrt(pow(city[0].X-city[n-1].X,2)+pow(city[0].Y-city[n-1].Y,2));
        for(int i = 0; i < num_max; i++)
        {
            swap(city, n);
            for( j = 0; j < n-1; j++)
            {
                s = s + sqrt(pow(city[j+1].X-city[j].X,2)+pow(city[j+1].Y-city[j].Y,2));
            }
            s = s + sqrt(pow(city[0].X-city[n-1].X,2)+pow(city[0].Y-city[n-1].Y,2));
            if(s < rult)
            {
                rult = s;

                for( i = 0; i < n; i++)
                {
                   rt[i] = city[i].CityName;
                }
                rt[n] = rt[0];
            }
        }
        return rult;
    }
};

int main()
{
    int i,j;
    SimulatedAnnealing a;
    int num;
    int dtc;
    ifstream infile;
    infile.open("Lab5_partI_input.txt",ios::in);
    infile>>num;
    City *city1 = new City[num];
    for(i = 0; i < num; i++)
    {
        infile>>city1[i].CityName>>city1[i].X>>city1[i].Y;
    }
    infile.close();

    int *rt1 = new int[num+1];
    for(i = 0; i < num; i++)
    {
        rt1[i] = city1[i].CityName;
    }
    rt1[num] = rt1[0];
    dtc = a.Annealing(city1, rt1, num);
    ofstream outfile;
    outfile.open("Lab5_partI_task1_output.txt",ios::out);
    outfile<<"The results of SA Method: "<<dtc<<endl;
    for(i = 0;i<num+1;i++)
        outfile<<rt1[i]<<endl;
    outfile.close();

    Greedy b;
    infile.open("Lab5_partI_input.txt",ios::in);
    infile>>num;
    City *city2 = new City[num];
    for(j = 0; j < num; j++)
    {
       infile>>city2[j].CityName>>city2[j].X>>city2[j].Y;
    }
    infile.close();

    int *rt2 = new int[num+1];
    for(j = 0; j < num; j++)
    {
        rt2[j] = city2[j].CityName;
    }
    rt2[num] = rt2[0];

    dtc = b.GreedyM(city2, rt2, num);
    outfile.open("Lab5_partI_task2_output.txt");
    outfile<<"The results of Greedy Method: "<<dtc<<endl;
    for(j = 0;j<num+1;j++) {
        outfile << rt2[j] << endl;
    }
    outfile.close();

    delete []city1;
    delete []rt1;
    delete []city2;
    delete []rt2;

    return 0;
}