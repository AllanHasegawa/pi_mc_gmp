#include <iomanip>
#include <iostream>
#include <vector>
#include <random>
#include <future>
#include <algorithm>
#include "gmpxx.h"

long parallelF(const int precision, const long samples) {
	// using Mersene Twister engine
	gmp_randclass r1(gmp_randinit_mt);

	// seed providade by a random device (implementation defined)
	r1.seed(std::random_device{}());

	mpf_class x(0, precision);
	mpf_class y(0, precision);
	int counter{};
	for (int i = 0; i < samples; ++i) {
		//from GMP doc:
		//"if prec is not given then to the precision of the destination"
		x = r1.get_f();
		y = r1.get_f();
		x = x*x;
		y = y*y;
		if (x+y <= 1) ++counter;
	}
	return counter;
}


int main(void) {
	using namespace std;
	// precision ;)
	const int kPrecisionBits = 512;
	const int kNThreads = 16;
	// divide the work equally between each thread
	const long kSamples = 90000000 * kNThreads;

	vector<future<long>> asyncsHandler;

	for (int i = 0; i < kNThreads; ++i) {
		asyncsHandler.push_back(
			async(std::launch::async,
				[]{ return parallelF(kPrecisionBits, kSamples/kNThreads); }
			));
	}


	long counter{};
	for_each(asyncsHandler.begin(), asyncsHandler.end(),
		[&counter](future<long>& result) {
			counter += result.get();
		});

	mpf_class pi(0, kPrecisionBits);
	pi = counter;

	// pi = (counter*4)/samples
	pi = pi*4;
	pi = pi/(kSamples);

	cout << setprecision(200);
	cout << pi << endl;

	return 0;
}
