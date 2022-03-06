#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <array>
#include <limits>
#include <numeric>
#include <windows.h>

using namespace std;

class Player {};

class GameBoard
{
public:

	Player Player1, Player2;
	Player& const Turn = Player1;

	GameBoard() : Turn(Player1)
	{
	}

private:
	int board[10][10];
};

int main()
{
	char command = 0;
	bool done = false;

	cin.clear();

	while (true)
	{
		if (done) break;

		cout << "명령어 입력: ";
		cin >> command;

		command = toupper(command);

		switch (command)
		{
			case 'A': // 행을 따라 오름차순 정렬
			{

			}
			break;
		}
	}
}
