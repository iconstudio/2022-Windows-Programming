#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <array>
#include <limits>
#include <numeric>
#include <vector>
#include <stack>

using namespace std;

int to_int(string& str)
{
	int result = 0;

	int temp = 0, index = 0;
	for (auto it = str.cbegin(); it != str.cend(); ++it, ++index)
	{
		temp = *it;
		result += temp * pow(10, index);
	}

	return result;
}

float ProceedCalc(string& expression)
{
	vector<int> commands;
	vector<float> numbers;
	float result = 0;

	int bracketed = 0;
	string numerics, child_expr;
	auto near_end = expression.end() - 1;
	float result_multiply = 0, result_plus = 0;

	auto StackNumber = [&]() {
		if (0 < numerics.size())
		{
			auto number = to_int(numerics);
			commands.push_back(number);
			numerics.clear();
		}
	};

	for (auto it = expression.begin(); it != expression.end(); ++it)
	{
		auto cmd = *it;
		auto sz_cmd = commands.size();

		switch (cmd)
		{
			case '(':
			{
				bracketed++;
			}
			break;

			case ')':
			{
				if (0 < bracketed)
				{
					float child_result = ProceedCalc(child_expr);
					commands.push_back(child_result);
					bracketed--;
				}
				else
				{
					exit(1);
				}
			}
			break;

			case '.':
			{

			}
			break;

			case '+':
			case '-':
			case '*':
			case '/':
			{
				if (0 < bracketed) // 연산 안 하고 자식에게 넘겨주기
				{
					child_expr.push_back(cmd);
				}
				else // 연산
				{
					StackNumber();
					commands.push_back(cmd);
					/*
					if (cmd == '*')
					{
						auto before = it - 1;
						auto next = it + 1;
						commands.push_back();
					}
					else if (cmd == '/')
					{

					}
					else if (cmd == '+')
					{

					}
					else if (cmd == '-')
					{

					}*/
				}
			}
			break;

			default:
			{
				if (isdigit(cmd))
				{
					if (0 < bracketed) // 연산 안 하고 자식에게 넘겨주기
					{
						child_expr.push_back(cmd);
					}
					else // 연산
					{
						numerics.push_back(cmd);

						if (2 <= sz_cmd)
						{
							auto value = numbers.back();
							numbers.pop_back();
						}
					}
				}
			}
			break;
		} // switch
	}

	return result;
}

int main()
{
	string cmd;
	bool done = false;

	cin.clear();
	int bracketed = 0;
	float result = 0;

	while (true)
	{
		if (done) break;

		cout << "계산식 입력: ";
		cin >> cmd;

		result = ProceedCalc(cmd);

		cout << "결과: " << result << '\n';
	}
}
