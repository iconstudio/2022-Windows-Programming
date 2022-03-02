#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <array>
#include <numeric>

using namespace std;

int main() {
	random_device r_device;
	uniform_int_distribution<> r_distribution(1, 50);
	default_random_engine r_engine(r_device());

	array<int, 50> datas;
	iota(datas.begin(), datas.end(), 1);

	generate(datas.begin(), datas.end(), [&]() { return r_distribution(r_engine); });


}
