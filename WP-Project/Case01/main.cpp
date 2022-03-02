#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <array>
#include <numeric>

using namespace std;

class Matrix {
public:
	class horizontal_iterator {
	public:
		using iterator_category = random_access_iterator_tag;
		using element_type = int;
		using pointer = element_type*;
		using reference = element_type&;

		horizontal_iterator(Matrix* cont, size_t ind = 0)
			: container(cont), index(ind) {}

		horizontal_iterator(const horizontal_iterator& other)
			: container(other.container)
			, index(other.index)
			, x(other.x), y(other.y) {}

		constexpr reference operator*() noexcept {
			return const_cast<reference>(container->matrix[y][x]);
		}

		constexpr pointer operator->() const noexcept {
			return pointer_traits<pointer>::pointer_to(container->matrix[y][x]);
		}

		horizontal_iterator& operator++() noexcept {
			index++;
			Update();
			return *this;
		}

		horizontal_iterator operator++(int) noexcept {
			horizontal_iterator temp = *this;
			index++;
			Update();
			return temp;
		}

		horizontal_iterator& operator--() noexcept {
			index--;
			Update();
			return *this;
		}

		horizontal_iterator operator--(int) noexcept {
			horizontal_iterator temp = *this;
			index--;
			Update();
			return temp;
		}

		horizontal_iterator& operator+=(const size_t _Off) noexcept {
			index += _Off;
			Update();
			return *this;
		}

		horizontal_iterator operator+(const size_t _Off) const noexcept {
			horizontal_iterator temp = *this;
			temp += _Off;
			return temp;
		}

		horizontal_iterator& operator-=(const size_t _Off) noexcept {
			index -= _Off;
			Update();
			return *this;
		}

		horizontal_iterator operator-(const size_t _Off) const noexcept {
			horizontal_iterator temp = *this;
			temp -= _Off;
			return temp;
		}

		horizontal_iterator& operator+=(const horizontal_iterator& other) {
			index += other.index;
			Update();
			return *this;
		}

		horizontal_iterator operator+(const horizontal_iterator& other) const {
			horizontal_iterator temp = *this;
			temp += other.index;
			return temp;
		}

		horizontal_iterator& operator-=(const horizontal_iterator& other) {
			horizontal_iterator temp = *this;
			temp -= other.index;
			return *this;
		}

		bool operator==(const horizontal_iterator& other) {
			return (&container == &other.container && index == other.index);
		}

	private:
		Matrix* container;
		size_t index;
		size_t x, y;

		void Update() {
			size_t x = static_cast<size_t>(index % container->sz_w);
			size_t y = static_cast<size_t>(index / container->sz_w);
		}
	};

	Matrix(const size_t w, const size_t h, const size_t value = 0)
		: sz_w(w), sz_h(h), size(w* h), matrix(new int* [h]) {
		for (int i = 0; i < h; ++i) {
			matrix[i] = new int[w] {0};
			//fill(&(matrix[i][0]), &(matrix[i][w]), value);
		}
	}

	Matrix(const Matrix&& other)
		: sz_w(other.sz_w), sz_h(other.sz_h), size(other.size)
		, matrix(move(other.matrix)) {}

	const inline horizontal_iterator begin() noexcept {
		return horizontal_iterator(this, 0);
	}

	const inline horizontal_iterator end() noexcept {
		return horizontal_iterator(this, size);
	}
	bool operator==(Matrix& other) {
		if (size == other.size && sz_w == other.sz_w && sz_h == other.sz_h) {
			return false;
		} else {
			auto miss = search(begin(), end(), other.begin(), other.end());
			if (miss == end()) {
				return (size == other.size && sz_w == other.sz_w && sz_h == other.sz_h);
			} else {
				return false;
			}
		}
	}

	const size_t sz_w, sz_h, size;
	int** matrix = nullptr;
};

template<>
struct iterator_traits<Matrix::horizontal_iterator> {
	using iterator_category = random_access_iterator_tag;
	using element_type = int;
	using value_type = int;
	using pointer = element_type*;
	using reference = element_type&;
	using difference_type = size_t;
};

int main() {
	Matrix matrix{ 5, 4 };
	char command = 0;
	bool done = false;

	random_device r_device;
	uniform_int_distribution<> r_distribution(1, 50);
	default_random_engine r_engine(r_device());

	array<int, 50> numbers;
	iota(numbers.begin(), numbers.end(), 1);
	shuffle(numbers.begin(), numbers.end(), r_engine);
	copy_n(numbers.begin(), matrix.size, matrix.begin());
	//for_each(matrix.begin(), matrix.end(), [&](int& elem) { cout << elem << ", ";});
	cout << endl;

	cin.clear();

	while (true) {
		if (done) break;

		cout << "명령어 입력: ";
		cin >> command;

		command = toupper(command);

		switch (command) {
			case 'A':
			{
			}
			break;
		}
	}
}
