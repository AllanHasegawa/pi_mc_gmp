#include <iomanip>
#include <iostream>
#include <random>
#include "gmpxx.h"

int main(void) {
	using namespace std;
	// precision ;)
	const int kPresicionBits = 512;
	const int kSamples = 9000000;

	// using Mersene Twister engine
	gmp_randclass r1(gmp_randinit_mt);

	// seed providade by a random device (implementation defined)
	r1.seed(random_device{}());

	mpf_class x(0, kPresicionBits);
	mpf_class y(0, kPresicionBits);
	int counter{};
	for (int i = 0; i < kSamples; ++i) {
		x = r1.get_f();
		y = r1.get_f();
		x = x*x;
		y = y*y;
		if (x+y < 1) ++counter;
	}

	mpf_class pi(0, kPresicionBits);
	pi = counter;
	pi = pi*4;
	pi = pi/kSamples;
	
	cout << setprecision(200);
	cout << pi << endl;

	return 0;
}
