#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <array>
#include <limits>
#include <numeric>

using namespace std;

class Matrix {
public:
	Matrix(const size_t w, const size_t h, const size_t value = 0)
		: sz_w(w), sz_h(h), size(w * h)
		, matrix(new int* [w]) {
		for (int i = 0; i < w; ++i) {
			matrix[i] = new int[h] {0};
			//fill(&(matrix[i][0]), &(matrix[i][w]), value);
		}
	}

	Matrix(const Matrix& other) = default;

	size_t GetWidth() const { return sz_w; }
	size_t GetHeight() const { return sz_w; }

	void Set(size_t x, size_t y, int value) {
		auto& place = At(x, y);
		place = value;
	}

	void Set(size_t index, int value) {
		auto& place = At(index);
		place = value;
	}

	int& At(size_t x, size_t y) const {
		return (matrix[y][x]);
	}

	int& At(size_t index) const {
		size_t x = (index % sz_w);
		size_t y = (index / sz_w);
		return At(x, y);
	}

	template <typename Predicate>
	void Foreach(Predicate predicate) {
		for (int j = 0; j < sz_h; ++j) {
			for (int i = 0; i < sz_w; ++i) {
				auto& place = At(i, j);
				predicate(place);
			}
		}
	}

	template <typename Predicate>
	void ForeachH(const size_t y, Predicate predicate) {
		for (int i = 0; i < sz_w; ++i) {
			auto& place = At(i, y);
			predicate(place);
		}
	}

	template <typename Predicate>
	void ForeachV(const size_t x, Predicate predicate) {
		for (int j = 0; j < sz_h; ++j) {
			auto& place = At(x, j);
			predicate(place);
		}
	}

	void Print() {
		for (int i = 0; i < sz_h; ++i) {
			PrintH(i);
		}
	}

	void PrintH(const size_t y) {
		for (int i = 0; i < sz_w; ++i) {
			auto& place = At(i, y);
			auto org = cout.width(2);
			cout << place << " ";
			cout.width(org);
		}
		cout << '\n';
	}

	template<typename Predicate>
	void PrintH_If(const size_t y, Predicate predicate) {
		for (int i = 0; i < sz_w; ++i) {
			auto& place = At(i, y);
			if (predicate(place)) {
				auto org = cout.width(2);
				cout << place << " ";
				cout.width(org);
			}
		}
		cout << '\n';
	}

	const size_t sz_w, sz_h, size;
	int** matrix = nullptr;
};

int main() {
	Matrix matrix{ 5, 4 };
	char command = 0;
	bool done = false;

	random_device r_device;
	default_random_engine r_engine(r_device());

	array<int, 50> numbers;
	iota(numbers.begin(), numbers.end(), 1);
	shuffle(numbers.begin(), numbers.end(), r_engine);

	int index = 0;
	for_each_n(numbers.begin(), matrix.size, [&](int number) {
		matrix.Set(index++, number);
	});

	matrix.Print();
	cout << endl;

	cin.clear();

	while (true) {
		if (done) break;

		cout << "명령어 입력: ";
		cin >> command;

		command = toupper(command);

		switch (command) {
			case 'A': // 행을 따라 오름차순 정렬
			{

			}
			break;

			case 'D': // 열을 따라 내림차순 정렬
			{
			}
			break;

			case 'E': // 짝수
			{
			}
			break;

			case 'O': // 홀수
			{
			}
			break;

			case 'M': // 최대
			{
				auto max = numeric_limits<int>::min();
				matrix.Foreach([&](int value) {
					if (max < value) {
						max = value;
					}
				});
				cout << "최대값: " << max << '\n';
			}
			break;

			case 'N': // 최소
			{
				int min = numeric_limits<int>::max();
				matrix.Foreach([&](int value) {
					if (value < min) {
						min = value;
					}
				});
				cout << "최소값: " << min << '\n';
			}
			break;

			case 'P': // 행의 값을 합해 1열에 저장
			{
				auto height = matrix.GetHeight();
				auto summary = new int[height];

				for (int i = 0; i < height; ++i) {
					summary[i] = 0;

					matrix.ForeachH(i, [&](int value) {
						summary[i] += value;
					});
				}

				for (int i = 0; i < height; ++i) {
					matrix.Set(0, i, summary[i]);
				}

				matrix.Print();
			}
			break;

			case 'R': // 무작위 재정렬
			{
			}
			break;

			case 'S': // 다시 값 입력받기 시작
			{
			}
			break;

			case 'Q': // 종료
			{
				done = true;
			}
			break;

		}
	}
}
