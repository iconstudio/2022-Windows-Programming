#include <iostream>
#include <string>
#include <algorithm>
#include <random>

using namespace std;

bool IsLowerCase(char ch) {
	return (97 <= ch && ch <= 122);
}
bool IsUpperCase(char ch) {
	return (65 <= ch && ch <= 90);
}

int main() {
	string inputs;
	char command = 0;
	bool done = false;

	random_device r_device;
	uniform_int_distribution<> r_distribution(0, 3);
	default_random_engine r_engine(r_device());

	cout << "문장 입력: ";
	getline(cin, inputs, '.');

	const auto last = end(inputs);
	auto it = find(begin(inputs), last, ' ');

	if (last != it) {
		while (true) {
			it = adjacent_find(it, last, [](char lhs, char rhs) {
				return (lhs == ' ' && lhs == rhs);
			});

			if (last == it) {
				break;
			} else {
				inputs.erase(it);
			}
		}
	}

	cout << "정리된 문자열: " << inputs << '\n';
	cin.clear();

	const char blank_modifier[] = { '@', '%', '#', '.' };
	const auto blk_last = end(blank_modifier);
	bool blk_did = false;

	while (true) {
		if (done) break;

		cout << "명령어 입력: ";
		cin >> command;
		if (IsLowerCase(command)) {
			command -= 32;
		}

		switch (command) {
			case 'L':
			{
				auto result = count(inputs.begin(), inputs.end(), ' ');

				cout << "단어의 수: " << result + 1 << '\n';
			}
			break;
			case 'C':
			{
				for_each(inputs.begin(), inputs.end(), [&](char& value) {
					if (IsLowerCase(value)) {
						value -= 32;
					} else if (IsUpperCase(value)) {
						value += 32;
					}
				});

				cout << "결과: " << inputs << '\n';
			}
			break;
			case 'E':
			{
				bool check_e = false;
				auto ita = inputs.begin();
				auto end = inputs.end();

				string result, temp;
				auto temp_inserter = back_insert_iterator(temp);

				for (it = inputs.begin(); it != end; ++it) {
					const auto ch = (*it);

					if (' ' != ch) {
						temp_inserter = ch;
						if ('e' == ch || 'E' == ch) {
							check_e = true;
						}
					} else {
						// 출력
						if (check_e)
						{
							transform(temp.begin(), temp.end()
								, temp.begin(), toupper);
						}

						result += temp;
						result += ' ';
						temp.clear();
						check_e = false;
					}
				}
				inputs = move(result);

				cout << "결과: " << inputs << '\n';
			}
			break;
			case 'F':
			{
				if (blk_did) {
					for_each(inputs.begin(), inputs.end(), [&](char& value) {
						for_each(begin(blank_modifier), blk_last, [&](char org) {
							if (org == value) {
								value = ' ';
							}
						});
					});

					blk_did = false;
				} else {
					for_each(inputs.begin(), inputs.end(), [&](char& value) {
						if (' ' == value) {
							auto index = r_distribution(r_engine);
							auto print = blank_modifier[index];

							value = print;
						}
					});

					blk_did = true;
				}

				cout << "결과: " << inputs << '\n';
			}
			break;
			case 'A':
			{
				rotate(inputs.begin(), inputs.begin() + 1, inputs.end());

				cout << "결과: " << inputs << '\n';
			}
			break;
			case 'Q':
			{
				done = true;
			}
			break;
		}
	}
}
