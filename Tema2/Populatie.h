#include "vectordebiti.h"

class populatie {
	vector<vectordebiti> p;

public:
	populatie();
	float fitness(float g);
	void selectie(populatie& next);
	void mutate();
	void cross_over();
	void print(vectordebiti n);
	void print2(float n);
	float chance = 0.4;
	float b = 0.0005;
	vectordebiti best();
	vectordebiti a[5];

};