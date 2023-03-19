#include "Populatie.h"

populatie::populatie()
{
	for (int i = 0; i < 100; i++) {
		p.push_back(vectordebiti());
	}
}

float populatie::fitness(float g)
{
	return 1 / (g + 0.00001 - vectordebiti::a);
}

void populatie::selectie(populatie& next)
{
	std::vector<float> eval;
	float T = 0;
	std::vector<float> prob;
	std::vector<float> q;
	for (int i = 0; i < p.size(); i++) {
		eval.push_back(fitness(p[i].evalueaza()));
		T += eval[i];
	}
	for (int i = 0; i < p.size(); i++) {
		prob.push_back(eval[i] / T);
	}
	q.push_back(0);
	for (int i = 0; i < p.size(); i++) {
		q.push_back(q[i] + prob[i]);
		
	}
	vectordebiti f;
	for (int i = 0; i < 10; i++) {
		vectordebiti f;
		f = p[0];
		next.p[i] = best();
		if (i % 3) { a[0] = a[1]; a[1] = a[2]; a[2] = a[3]; a[3] = a[4]; a[4] = best(); }
	}
	//print(best());
	//print2(fitness(best().evalueaza()));
	for (int i = 2; i < p.size(); i++) {
		float r = float(vectordebiti::generator() % 100000) / 100000;
		for (int j = 0; j < q.size() - 1; j++) {
			if (q[j] < r && r <= q[j + 1]) {
				next.p[i] = p[j];
				break;
			}
		}
	}
}

float rast(float a) {
	return a * a * 0.9*(vectordebiti::dimensiune / 30);
}

void populatie::mutate()
{
	if (vectordebiti::function == "rastrigin") { b = 0.003; };
	for (int i = 1; i < p.size()-1; i++) {
		b = fabs(0.003 - rast(fitness(p[i].evalueaza())));
		//if (a[0] == a[1] && a[1] == a[2] && a[2] == a[3] && a[3] == a[4]) { b = b+b/10; }else{b = 0.003;};
		for (int j = 0; j < p[i].bitvector.size(); j++) {
			if (float(vectordebiti::generator() % 100000) / 100000 < b) {
				p[i].vecin(j);
			}
		}
		
	}
}


void populatie::cross_over()
{
	int pos = vectordebiti::generator() % vectordebiti::dimensiune;
	if (pos == 0) { pos++; };
	//if (a[0] == a[1] && a[1] == a[2] && a[2] == a[3] && a[3] == a[4]) { chance = 0.6 ; };
	for (int i = 1; i < p.size() - 1; i++) {
		if (float(vectordebiti::generator() % 100000) / 100000 < chance) {
			p[i].cross_over(p[pos]);
		}
	}
}


vectordebiti populatie::best()
{
	int best = 0;
	for (int i = 1; i < p.size(); i++) {
		if (fitness(p[i].evalueaza()) > fitness(p[best].evalueaza())) {
			best = i;
		}
	}
	return p[best];
}

void populatie::print(vectordebiti n){
		cout<<n.evalueaza()<<endl;
};

void populatie::print2(float n) {
	cout << n << endl;
};