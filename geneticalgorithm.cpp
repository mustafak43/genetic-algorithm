#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

const string alph = "abcdefghijklmnopqrstuvwxyz ";

// General.Settings
// - only lower case is supported
struct Settings
{
    string TAR; // target string
    int    LEN; // target string length
    int    POP; // population size
    int    MUT; // mutation rate
    int    CRO; // crossover chance
    Settings()
    {
        // default settings
        TAR = "";
        LEN = 0;
        POP = 0;
        MUT = 3;
        CRO = 70;
    }
}SET; // short for settings

// optional struct
// for trivial informations
struct Count
{
    size_t crossOver;
    size_t generation;
    size_t mutation;
    Count()
    {
        // initial values
        crossOver = 0;
        generation = 1;
        mutation = 0;
    }
}COUNT;

string rand_str(int l);
char   rand_chr();

class GeneticAlgorithm
{
private:
    const size_t size;
    vector<string> pop; // population
    vector<size_t> fit; // fitness
public:
    GeneticAlgorithm(size_t s, int l)
        : size(s)
    {
        for (size_t i = 0; i < s; i++)
        {
            pop.push_back(rand_str(l));
            // fitnesses are set to 0
            fit.push_back(0);
        }
    }

    void mutate()
    {
        for (size_t i = 0; i < size; i++)
        {
            for (size_t j = 0; j < pop[i].length(); j++)
            {
                if (rand() % 100 < SET.MUT)
                {
                    pop[i][j] = rand_chr();

                    COUNT.mutation++;
                }
            }
        }
    }

    // index of fittest offspring
    size_t fittest()
    {
        // temp for fitness value
        size_t temp = 0;
        // index val to be returned
        size_t index = 0;

        for (size_t i = 0; i < size; i++)
        {
            if (fit[i] > temp)
            {
                temp = fit[i];
            }
        }

        for (size_t i = 0; i < size; i++)
        {
            if (fit[i] == temp)
            {
                index = i;
            }
        }

        return index;
    }

    // is target found?
    bool found()
    {
        for (size_t i = 0; i < size; i++)
        {
            if (pop[i] == SET.TAR)
                return true;
        }
        return false;
    }

    void evaluate()
    {
        for (size_t i = 0; i < size; i++)
        {
            int fitness = 0;

            for (size_t j = 0; j < pop[i].length(); j++)
            {
                if (pop[i][j] == SET.TAR[j])
                {
                    fitness++;
                }
            }

            fit[i] = fitness;
        }
    }

    void rePopulate()
    {
        string parent = pop[fittest()];

        for (size_t i = 0; i < size; i++)
        {
            if (rand() % 100 < SET.CRO)
            {
                if (rand() % 2 == 0)
                {
                    for (size_t j = 0; j < parent.length() / 2; j++)
                    {
                        pop[i][j] = parent[j];
                    }
                }
                else
                {
                    for (size_t j = parent.length() / 2; j < parent.length(); j++)
                    {
                        pop[i][j] = parent[j];
                    }
                }

                COUNT.crossOver++;
            }
        }

        mutate();

        COUNT.generation++;
    }

    void print()
    {
        for (size_t i = 0; i < pop.size(); i++)
        {
            cout << "offspring " << i + 1 << ": ";
            cout << pop[i] << endl;
        }
    }
};


int main()
{
    // <setup>
    srand(time(0));

    SET.TAR = "to be or not to be";
    SET.LEN = SET.TAR.length();
    SET.POP = 10;

    GeneticAlgorithm ga(SET.POP, SET.LEN);
    // <\setup>
    // ---------------------------------
    // <body>
    while (!ga.found())
    {
        ga.evaluate();
        ga.rePopulate();
    }
    // <\body>
    // ---------------------------------
    // <final>
    ga.evaluate();
    ga.print();

    cout << endl;
    cout << "Cross-over count  : " << COUNT.crossOver << endl;
    cout << "Mutation count    : " << COUNT.mutation << endl;
    cout << "Found at " << COUNT.generation << "th generation" << endl;
    cout << ga.fittest() + 1;

    switch (ga.fittest() + 1)
    {
    case 1:
        cout << "st offspring";
        break;
    case 2:
        cout << "nd offspring";
        break;
    case 3:
        cout << "rd offspring";
        break;
    default:
        cout << "th offspring";
        break;
    }

    // <\final>

    return 0;
}

string rand_str(int l)
{
    string str = "";

    for (int i = 0; i < l; i++)
    {
        str += rand_chr();
    }

    return str;
}

char rand_chr()
{
    return alph[rand() % alph.length()];
}