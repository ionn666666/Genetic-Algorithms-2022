#include <iostream>
#include "vectordebiti.h"


float de_jong_minimum = -5.12;
float de_jong_interval = 10.24;

float schwefel_minimum = -500;
float schwefel_interval = 1000;

float rastrigin_minimum = -5.12;
float rastrigin_interval = 10.24;

float michalewicz_minimum = 0;
float michalewicz_interval = 3.14159;

int main()
{
    time_t start, end;
    time(&start);
    //srand(time(NULL));
    cout << "hello" << endl;
    vectordebiti::function = "rastrigin";//de_jong;schwefel;rastrigin;michalewicz
    vectordebiti::iteratii = 1000;
    string algorithm = "HillClimbing";//SimulatedAnnealing;HillClimbing
    vectordebiti::subalg = "worst";//first;best;worst
    vectordebiti::dimensiune = 5;//5;10;30

    vectordebiti x;
    if (x.function == "de_jong") {
        vectordebiti::interval = de_jong_interval;
        vectordebiti::minimum = de_jong_minimum;
    }
    else if (x.function == "schwefel") {
        vectordebiti::interval = schwefel_interval;
        vectordebiti::minimum = schwefel_minimum;
    }
    else if (x.function == "rastrigin") {
        vectordebiti::interval = rastrigin_interval;
        vectordebiti::minimum = rastrigin_minimum;
    }
    else if (x.function == "michalewicz") {
        vectordebiti::interval = michalewicz_interval;
        vectordebiti::minimum = michalewicz_minimum;
    }

    vectordebiti::NumarDeBiti = ceilf(log2f(x.interval / 0.00001));
    vectordebiti::LungimeaArray = x.dimensiune * x.NumarDeBiti;

    int p = 1;
    for (int i = 0; i <= x.NumarDeBiti; i++) {
        vectordebiti::pow_2.push_back(p);
        p *= 2;
    }
    /*
    x.initializare();
    cout<<"marimea bitvec="<<x.bitvector.size()<<endl;
    cout << "marimea numvec=" << x.numarvector.size() << endl;
    cout << "lungarray=" << x.LungimeaArray << endl;
    cout << "dimensiune=" << x.dimensiune << endl;
    cout << "bitipernumar=" << x.NumarDeBiti << endl;
    cout << "marimea numvec=" << x.numarvector.size() << endl;
    */
    
    for (int i = 0; i < 30; i++) {
        vectordebiti y;
        /*
        cout << "marimea bitvec=" << y.bitvector.size() << endl;
        cout << "marimea numvec=" << y.numarvector.size() << endl;
        cout << "lungarray=" << y.LungimeaArray << endl;
        cout << "dimensiune=" << y.dimensiune << endl;
        cout << "bitipernumar=" << y.NumarDeBiti << endl;
        cout << "marimea numvec=" << y.numarvector.size() << endl; 
        */
        if (algorithm == "HillClimbing") {
            y.HillClimbing();
        }
        else if (algorithm == "SimulatedAnnealing") {
            y.SimulatedAnnealing();
        }
        y.print();
    }
    time(&end);
    int nothing;
    double time_taken = double(end - start);
    cout << "time taken by program:" << time_taken << endl;
    cin >> nothing;

}