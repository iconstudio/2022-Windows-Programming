#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <array>
#include <numeric>

using namespace std;

class Matrix {
public:
	Matrix(const size_t w, const size_t h, const int value = 0)
		: sz_w(w), sz_h(h), matrix(new int*[h]) {
		for (int i = 0; i < h; ++i) {
			matrix[i] = new int[w];
			fill(&(matrix[i]), &(matrix[i + w - 1]), 0);
		}
	}

private:
	const size_t sz_w, sz_h;
	int** matrix = nullptr;
};

int main() {
	Matrix matrix{ 5, 4 };
	char command = 0;
	bool done = false;

	random_device r_device;
	uniform_int_distribution<> r_distribution(1, 50);
	default_random_engine r_engine(r_device());
	r_distribution(r_engine);

	array<int, 50> numbers;
	iota(numbers.begin(), numbers.end(), 1);
	shuffle(numbers.begin(), numbers.end(), r_engine);

	cin.clear();

	const char blank_modifier[] = { '@', '%', '#', '.' };
	const auto blk_last = end(blank_modifier);
	bool blk_did = false;

	while (true) {
		if (done) break;

		cout << "명령어 입력: ";
		cin >> command;

		command = toupper(command);

		switch (command) {
			case 'L':
			{
			}
			break
		}
	}
}
