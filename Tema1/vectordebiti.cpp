#include "vectordebiti.h"

float vectordebiti::de_jong(std::vector<float> x) {
	float sum = 0;
	for (int i = 0; i < x.size(); i++) {
		sum += x[i] * x[i];
	}
	return sum;
}

float vectordebiti::schwefel(std::vector<float> x) {
	float sum = 0;
	for (int i = 0; i < x.size(); i++) {
		sum += -(x[i]) * sin(sqrt(fabs(x[i])));
	}
	return sum;
}

float vectordebiti::rastrigin(std::vector<float> x) {
	float sum = 0;
	for (int i = 0; i < x.size(); i++) {
		sum += x[i] * x[i] - 10 * cos(2 * 3.14159 * x[i]);
	}
	float result = 10 * dimensiune + sum;
	return result;
}

float vectordebiti::michalewicz(std::vector<float> x) {
	//n++; ////
	//cout << "evaluarea nr :" << n << endl; //////
	float sum = 0;
	//for (int i = 0; i < dimensiune; i++) {
	//	cout << "x[i]=" << x.at(i) << endl;}      /////////
	for (int i = 0; i < x.size(); i++) {
		sum += sinf(x[i]) * (pow(sinf((i+1) * x[i] * x[i] / 3.14159), 20));
	}
	float result = -sum;
	//cout <<"result mich=" << result << endl;///////////////

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
	for (int j = i * NumarDeBiti; j < (i + 1) * NumarDeBiti;j++) {
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
		//cout << "x=" << minimum + numarvector[i] / float(pow_2[NumarDeBiti] - 1) * interval << endl; /////
	}
	if (function == "de_jong") { return de_jong(x); };
	if (function == "schwefel") { return schwefel(x); };
	if (function == "rastrigin") { return rastrigin(x); };
	if (function == "michalewicz") { return michalewicz(x); };
}

void vectordebiti::vecin(int i) {
	bitvector[i] = !bitvector[i];
	int m = i / NumarDeBiti;
	int pos = NumarDeBiti - (i % NumarDeBiti);
	if (bitvector[i]) numarvector[m] += pow_2[pos - 1];
	else numarvector[m] -= pow_2[pos - 1];
}

const vectordebiti vectordebiti::firstImpr() {
	vectordebiti best(*this);
	float best_val = best.evalueaza();
	for (int i = 0; i < LungimeaArray; i++) {
		best.vecin(i);
		if (best.evalueaza() < best_val) break;
		best.vecin(i);
	}
	//cout << "bestF" <<endl;//////////////7
	return best;
}

const vectordebiti vectordebiti::bestImpr() {
	vectordebiti v_n(*this);
	vectordebiti best(*this);
	float best_val = best.evalueaza();
	for (int i = 0; i < LungimeaArray; i++) {
		v_n.vecin(i);
		float vn_val = v_n.evalueaza();
		if (vn_val < best_val) {
			best = v_n;
			best_val = vn_val;
		}
		v_n.vecin(i);
	}
	return best;
}

const vectordebiti vectordebiti::worstImpr() {
	vectordebiti v_n(*this);
	vectordebiti best(*this);
	float best_val = best.evalueaza();

	for (int i = 0; i < LungimeaArray; i++) {
		int j; j = generator() % LungimeaArray;
		v_n.vecin(j);
		float vn_val = v_n.evalueaza();
		if (vn_val < best_val) {
			best = v_n;
			best_val = vn_val;
		}
		v_n.vecin(j);
	}
	return best;
};


void vectordebiti::HillClimbing() {
	float best_val = this->evalueaza();
	//cout << "hill1" << endl;
	for (int i = 0; i < iteratii; i++) {
		vectordebiti v_c;
		while (true) {
			vectordebiti v_n;
			//cout << "v_n size=" << v_n.bitvector.size()<< endl;
			if (subalg == "first") { v_n = v_c.firstImpr(); }
			else if (subalg == "best") { v_n = v_c.bestImpr(); }
			else if (subalg == "worst") { v_n = v_c.worstImpr(); };
			//cout << "v_n = " << v_n.evalueaza() << endl;
			//cout << "v_n = " << v_c.evalueaza() << endl;
			if (v_n.evalueaza() < v_c.evalueaza())
				v_c = v_n;
			else break;
		}
		float vc_val = v_c.evalueaza();
		if (vc_val < best_val) {
			*this = v_c;
			best_val = vc_val;
		}
	}

};

void vectordebiti::SimulatedAnnealing() {
	float temperature = 1000;
	vectordebiti v_c;
	while (true) {
		float cur_solution = v_c.evalueaza();
		for (int i = 0; i < iteratii; i++) {
			int k = generator() % LungimeaArray;
			v_c.vecin(k);
			vectordebiti v_n(v_c);
			v_c.vecin(k);
			if (v_n.evalueaza() < v_c.evalueaza()) {
				v_c = v_n;
			}
			else if (float(generator() % 100000) / 100000 < expf(-fabsf(v_n.evalueaza() - v_c.evalueaza()) / temperature)) {
				v_c = v_n;
			}
		}
		if (cur_solution - v_c.evalueaza() == 0) break;
		temperature = temperature * 0.9;
	}
	*this = v_c;
}

void vectordebiti::print() {
	/*for (int i = 0; i < dimensiune - 1; i++) {
		cout<<this->numarvector[i]<<endl;
	}*/
	cout << fixed << setprecision(5) << this->evalueaza() << "\n";
}

mt19937 vectordebiti::generator(chrono::system_clock::now().time_since_epoch().count());
float vectordebiti::minimum, vectordebiti::interval;
int vectordebiti::NumarDeBiti, vectordebiti::dimensiune, vectordebiti::LungimeaArray;
vector<int> vectordebiti::pow_2;int vectordebiti::iteratii;string vectordebiti::subalg;
string vectordebiti::function;