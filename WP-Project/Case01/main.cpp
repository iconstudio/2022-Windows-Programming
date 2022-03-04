#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <array>
#include <numeric>

using namespace std;

class Matrix {
public:
	Matrix(const size_t w, const size_t h, const size_t value = 0)
		: sz_w(w), sz_h(h), size(w* h)
		, matrix(new int* [h]) {
		for (int i = 0; i < h; ++i) {
			matrix[i] = new int[w] {0};
			//fill(&(matrix[i][0]), &(matrix[i][w]), value);
		}
	}

	Matrix(const Matrix& other) = default;

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
	void Foreach(Predicate predicate)
	{
		for (int j = 0; j < sz_h; ++j)
		{
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

	template <typename Predicate>
	void PrintH(const size_t y) {
		for (int i = 0; i < sz_w; ++i) {
			auto& place = At(i, y);
			cout << place << " ";
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
			}
			break;

			case 'N': // 최소
			{
			}
			break;

			case 'P': // 행의 값을 합해 1열에 저장
			{
			}
			break;

			case 'R': // 무작위 재정렬
			{
				auto& _UFirst = matrix.At(0);
				auto& _ULast = matrix.At(matrix.size - 1);
				auto& _UTarget = matrix.At(0);
				size_t _Target_index = 1;

				for (; ++_Target_index < matrix.size - 1; ++_Target_index) {
					uniform_int_distribution<int> r_distribution(0, _Target_index + 1);

					size_t _Off = r_distribution(r_engine);
					if (_Off < 0 || _Target_index < _Off) {
						break;
					}

					if (_Off != _Target_index) {
						auto value = _UTarget;
						matrix.Set(_Target_index, value);
						matrix.Set(_Off, value);
					}
				}
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
