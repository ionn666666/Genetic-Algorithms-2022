#include <vector>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <limits>
#include <numbers>
#include <random>
#include <chrono>
#include <time.h>
#include <iostream>
using namespace std;

class vectordebiti {
public:
    vector<bool> bitvector;
    vector<int> numarvector;
    vector<bool> bitvector_2;

    void GeneticAlgorithm();
    vectordebiti();
    vectordebiti(const vectordebiti& v);
    static float minimum;
    static float a;
    static float interval;
    static int iteratii;
    static int NumarDeBiti;
    static int LungimeaArray;
    static int dimensiune;
    static mt19937 generator;
    static vector<int> pow_2;
    //void HillClimbing();
    //void SimulatedAnnealing();
    int genereaza_bit();
    int numar(int i);
    int bestval;
    void print();
    static string function;
    //static string subalg;
    //void vecin(int i);
    float fitness(float g);
    void operator=(const vectordebiti& v);
    bool operator==(const vectordebiti& v);
    //const vectordebiti firstImpr();
    //const vectordebiti bestImpr();
    //const vectordebiti worstImpr();
    float evalueaza();
    float de_jong(std::vector<float> x);
    float schwefel(std::vector<float> x);
    float rastrigin(std::vector<float> x);
    float michalewicz(std::vector<float> x);
    int n = 0;

    float eval(int x);
    void select();
    void mutate();
    void cross_over(vectordebiti& v);
    static float besteval;
    void Debug();
    void Debug2();
    void bestvalcalc();
    void populatie();
    void initializare();
    void vecin(int i);

};
