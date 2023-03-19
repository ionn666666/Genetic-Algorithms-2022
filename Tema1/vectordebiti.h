#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <limits>
#include <numbers>
#include <random>
#include <chrono>
#include <time.h>
using namespace std;

class vectordebiti {
public:
    vector<bool> bitvector;
    vector<int> numarvector;


    vectordebiti();
    vectordebiti(const vectordebiti& v);
    void initializare();
    static float minimum;
    static float interval;
    static int iteratii;
    static int NumarDeBiti;
    static int LungimeaArray;
    static int dimensiune;
    static mt19937 generator;
    static vector<int> pow_2;
    void HillClimbing();
    void SimulatedAnnealing();
    int genereaza_bit();
    int numar(int i);
    void print();
    static string function;
    static string subalg;
    void vecin(int i);
    void operator=(const vectordebiti& v);
    const vectordebiti firstImpr();
    const vectordebiti bestImpr();
    const vectordebiti worstImpr();
    float evalueaza();
    float de_jong(std::vector<float> x);
    float schwefel(std::vector<float> x);
    float rastrigin(std::vector<float> x);
    float michalewicz(std::vector<float> x);
    int n=0; ////
};