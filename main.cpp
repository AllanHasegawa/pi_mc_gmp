#include <iomanip>
#include <iostream>
#include <random>
#include "gmpxx.h"

int main(void) {
	using namespace std;
	// precision ;)
	const int kP = 90000;

	// using Mersene Twister engine
	gmp_randclass r1(gmp_randinit_mt);

	// seed providade by a random device (implementation defined)
	r1.seed(random_device{}());
	cout << setprecision(kP);

	cout << r1.get_f(kP) << endl;

	mpf_t sum;
	mpf_init(sum);
	mpf_set_str(sum, "12345", 10);
	cout << sum << endl;
	mpf_clear(sum);
	int i{};
	cout << i << endl;
	return 0;
}
