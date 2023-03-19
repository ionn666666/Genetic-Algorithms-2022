#include "vectordebiti.h"

float vectordebiti::de_jong(std::vector<float> x) {
	float sum = 0;
	for (int i = 0; i < x.size(); i++) {
		sum += x[i] * x[i];
	}
	//cout << "suma functie este" << sum << endl;
	return sum;
}

float vectordebiti::schwefel(std::vector<float> x) {
	float sum = 0;
	for (int i = 0; i < x.size(); i++) {
		sum += -(x[i]) * sinf(sqrtf(fabsf(x[i])));
	}
	//cout << "suma functie este" << sum << endl;
	return sum;
}

float vectordebiti::rastrigin(std::vector<float> x) {
	float sum = 0;
	for (int i = 0; i < x.size(); i++) {
		sum += x[i] * x[i] - 10 * cosf(2.0f * 3.14159f * x[i]);
	}
	float result = 10 * dimensiune + sum;
	return result;
}

float vectordebiti::michalewicz(std::vector<float> x) {
	float sum = 0;
	for (int i = 0; i < x.size(); i++) {
		sum += sinf(x[i]) * (pow(sinf((i+1) * x[i] * x[i] / 3.14159), 20));
	}
	float result = -sum;
	return result;
}

vectordebiti::vectordebiti() {
	initializare();
};

vectordebiti::vectordebiti(const vectordebiti& v) {
	for (int i = 0; i < LungimeaArray; i++) {
		bitvector.push_back(v.bitvector[i]);
	}
	for (int i = 0; i < dimensiune; i++) {
		numarvector.push_back(v.numarvector[i]);
	}
}

int vectordebiti::genereaza_bit() {
	return(generator() % 2);
};

void vectordebiti::initializare() {
	for (int i = 0; i < LungimeaArray; i++) {
		bitvector.push_back(genereaza_bit());
	}
	for (int i = 0; i < dimensiune; i++) {
		numarvector.push_back(numar(i));
	}
};

int vectordebiti::numar(int i) {
	int suma = 0;
	for (int j = i * NumarDeBiti; j < (i + 1) * NumarDeBiti; j++) {
		suma = suma * 2 + bitvector[j];
		
	}
	return suma;
};


void vectordebiti::operator=(const vectordebiti& v) {
	for (int i = 0; i < LungimeaArray; i++) {
		bitvector[i] = v.bitvector[i];
	}
	for (int i = 0; i < dimensiune; i++) {
		numarvector[i] = v.numarvector[i];
	}
}

float vectordebiti::evalueaza() {
	vector<float> x;

	for (int i = 0; i < dimensiune; i++) {
		x.push_back(minimum + numarvector[i] / float(pow_2[NumarDeBiti] - 1) * interval);
	}

	if (function == "de_jong") { return de_jong(x); };
	if (function == "schwefel") { return schwefel(x); };
	if (function == "rastrigin") { return rastrigin(x); };
	if (function == "michalewicz") { return michalewicz(x); };
	return 0;
}

float vectordebiti::eval(int y) {
	vector<float> x;

	x.push_back(minimum + numarvector[y] / float(pow_2[NumarDeBiti] - 1) * interval);
	if (function == "de_jong") { return de_jong(x); };
	if (function == "schwefel") { return schwefel(x); };
	if (function == "rastrigin") { return rastrigin(x); };
	if (function == "michalewicz") { return michalewicz(x); };
	return 0;
};

float vectordebiti::fitness(float g)
{
	return 1 / (g + 0.00001 - minimum);
}

void vectordebiti::vecin(int i) {
	bitvector[i] = !bitvector[i];
	int m = i / NumarDeBiti;
	int pos = NumarDeBiti - (i % NumarDeBiti);
	if (bitvector[i]) numarvector[m] += pow_2[pos - 1];
	else numarvector[m] -= pow_2[pos - 1];
}


void vectordebiti::cross_over(vectordebiti& v)
{
	int cut = generator() % NumarDeBiti;
	for (int i = 0; i < cut; i++) {
		bool temp = bitvector[i];
		bitvector[i] = v.bitvector[i];
		v.bitvector[i] = temp;
	}
	for (int i = 0; i < dimensiune; i++) {
		numarvector[i] = numar(i);
		v.numarvector[i] = v.numar(i);
	}
}

bool vectordebiti::operator==(const vectordebiti& v) {
	bool a = true;
	for (int i = 0; i < NumarDeBiti; i++) {
		if (bitvector[i] != v.bitvector[i]) { a = false; };
	}
	return a;
}

void vectordebiti::Debug() {
	cout << "biti sunt :" << endl;
	for (int i = 0; i < LungimeaArray; i++) {
		cout<<bitvector[i];
	}
	cout << endl;

	cout << "numerele sunt :" << endl;
	for (int i = 0; i < dimensiune; i++) {
		cout << numarvector[i] <<endl;
	}
	cout << endl;
	
	cout << "rezultatele sunt :" << endl;
	for (int i = 0; i < dimensiune; i++) {
		cout << fixed << setprecision(5) << eval(i) << endl;
	}
	cout << endl;

	cout << "evaluarea curenta este :" << endl;
	cout << evalueaza() << endl;

};

void vectordebiti::Debug2() {
	
	cout << evalueaza() << endl;

};

void vectordebiti::print() {
	/*for (int i = 0; i < dimensiune - 1; i++) {
		cout<<this->numarvector[i]<<endl;
	}*/
	cout << fixed << setprecision(5) << this->evalueaza() << "\n";
}

mt19937 vectordebiti::generator(chrono::system_clock::now().time_since_epoch().count());
float vectordebiti::minimum, vectordebiti::interval;
int vectordebiti::NumarDeBiti, vectordebiti::dimensiune, vectordebiti::LungimeaArray;
vector<int> vectordebiti::pow_2; int vectordebiti::iteratii; /*string vectordebiti::subalg*/;
string vectordebiti::function;
float vectordebiti::besteval; float vectordebiti::a;