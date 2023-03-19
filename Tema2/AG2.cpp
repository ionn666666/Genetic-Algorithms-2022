//#include "vectordebiti.h"
#include "Populatie.h"


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
    cout << "hello" << endl;
    vectordebiti::function = "rastrigin";//de_jong;schwefel;rastrigin;michalewicz
    vectordebiti::iteratii = 2000;
    vectordebiti::dimensiune = 30;
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

    vectordebiti::a = 0;
    if ("schwefel" == x.function) {
        vectordebiti::a = -419 * vectordebiti::dimensiune;
    }
    else if ("michalewicz" == x.function) {
        vectordebiti::a = -vectordebiti::dimensiune;
    }

    vectordebiti::NumarDeBiti = ceilf(log2f(x.interval / 0.00001));
    vectordebiti::LungimeaArray = x.dimensiune * x.NumarDeBiti;

    int p = 1;
    for (int i = 0; i <= x.NumarDeBiti; i++) {
        vectordebiti::pow_2.push_back(p);
        p *= 2;
    }
 
    for (int i = 0; i < 30; i++) {
    populatie y;
    populatie next;
    //y.best().print();
    for (int i = 0; i < vectordebiti::iteratii; i++) {
        //cout << "iteratia nr" << i << endl;
        y.selectie(next);
        next.mutate();
        next.cross_over();
        next.selectie(y);
        y.mutate();
        y.cross_over();
        //if (i > 500) { y.b = 0.001; y.chance = 0.4; next.b = 0.001; next.chance = 0.4; }
    }
    y.best().print();
    }
    /*
        vectordebiti y;
        y.geneticalgorithm();
        cout << "last debug" << endl;
        y.debug();
    */

    time(&end);
    int nothing;
    double time_taken = double(end - start);
    cout << "time taken by program:" << time_taken << endl;
    cin >> nothing;

}