#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <array>
#include <limits>
#include <numeric>
#include <windows.h>

using namespace std;

random_device r_device;
default_random_engine r_engine{ r_device() };
uniform_int_distribution<> r_distribution(0, 4);

char MakeShape()
{
	const char candidates[5] = { 'o', 'x', '#', '@', '*' };
	const int index = r_distribution(r_engine);

	return candidates[index];
}

class Player
{
public:
	Player() : x(0), y(0), shape(MakeShape()) {}
	Player(int nx, int ny) : x(nx), y(ny), shape(MakeShape()) {}

	void MoveLeft()
	{
		if (--x < 0) x = 9;
	}
	void MoveRight()
	{
		if (10 <= ++x) x = 0;
	}
	void MoveUp()
	{
		if (--y < 0) y = 9;
	}
	void MoveDown()
	{
		if (10 <= ++y) y = 0;
	}
	constexpr bool operator==(const Player& other) const
	{
		return (this == &other);
	}

	int x, y;
	char shape;
};

class GameBoard
{
public:
	Player Player1, Player2;

	GameBoard() : Turn(&Player1)
	{
		Reset();
	}

	void SetTurn(const Player& player)
	{
		Turn = &player;
	}
	bool IsTurn(const Player& player)
	{
		return (*Turn == player);
	}
	void TurnGoNext()
	{
		if (IsTurn(Player1))
		{
			SetTurn(Player2);
		}
		else
		{
			SetTurn(Player1);
		}
	}
	void Reset()
	{
		Turn = &Player1;

		Player1.x = 1;
		Player1.y = 5;
		Player2.x = 7;
		Player2.y = 5;
	}
	void Prompt()
	{
		int p1_x = Player1.x, p1_y = Player1.y;
		int p2_x = Player2.x, p2_y = Player2.y;
		bool overlapped = (p1_x == p2_x && p1_y == p2_y);
		Player& winner = IsTurn(Player1) ? Player2 : Player1;

		cout << "+--+--+--+--+--+--+--+--+--+--+\n";
		for (int y = 0; y < 10; ++y)
		{
			cout << "|";

			for (int x = 0; x < 10; ++x)
			{
				bool p1_picked = (p1_x == x && p1_y == y);
				bool p2_picked = (p2_x == x && p2_y == y);

				if (p1_picked || p2_picked)
				{
					if (overlapped)
					{
						if (winner == Player1)
						{
							::Beep(1000, 500);
							Player2.shape = MakeShape();
							cout << "1";
						}
						else
						{
							::Beep(1000, 500);
							Player1.shape = MakeShape();
							cout << "2";
						}

						cout << winner.shape << "|";
					}
					else
					{
						if (p1_picked)
						{
							cout << "1" << Player1.shape << "|";
						}
						else
						{
							cout << "2" << Player2.shape << "|";
						}
					}
				}
				else
				{
					cout << " 0|";
				}
			}

			cout << "\n+--+--+--+--+--+--+--+--+--+--+\n";
		}
	}

private:
	Player const* Turn;
};

int main()
{
	GameBoard game;
	char command = 0;
	bool done = false;

	bool prompt = true;
	auto& player1 = game.Player1;
	auto& player2 = game.Player2;
	cin.clear();

	game.Prompt();
	while (true)
	{
		if (done) break;

		cout << "명령어 입력: ";
		cin >> command;

		command = toupper(command);

		switch (command)
		{
			case 'W': // 플레이어 1 상단 이동
			{
				prompt = game.IsTurn(player1);
				if (prompt)
				{
					player1.MoveUp();
					game.TurnGoNext();
				}
			}
			break;
			case 'A': // 플레이어 1 좌단 이동
			{
				prompt = game.IsTurn(player1);
				if (prompt)
				{
					player1.MoveLeft();
					game.TurnGoNext();
				}
			}
			break;
			case 'S': // 플레이어 1 하단 이동
			{
				prompt = game.IsTurn(player1);
				if (prompt)
				{
					player1.MoveDown();
					game.TurnGoNext();
				}
			}
			break;
			case 'D': // 플레이어 1 우단 이동
			{
				prompt = game.IsTurn(player1);
				if (prompt)
				{
					player1.MoveRight();
					game.TurnGoNext();
				}
			}
			break;
			case 'I': // 플레이어 2 상단 이동
			{
				prompt = game.IsTurn(player2);
				if (prompt)
				{
					player2.MoveUp();
					game.TurnGoNext();
				}
			}
			break;
			case 'J': // 플레이어 2 좌단 이동
			{
				prompt = game.IsTurn(player2);
				if (prompt)
				{
					player2.MoveLeft();
					game.TurnGoNext();
				}
			}
			break;
			case 'K': // 플레이어 2 하단 이동
			{
				prompt = game.IsTurn(player2);
				if (prompt)
				{
					player2.MoveDown();
					game.TurnGoNext();
				}
			}
			break;
			case 'L': // 플레이어 2 우단 이동
			{
				prompt = game.IsTurn(player2);
				if (prompt)
				{
					player2.MoveRight();
					game.TurnGoNext();
				}
			}
			break;

			case 'R':
			{
				prompt = true;
				game.Reset();
			}
			break;
			case 'Q':
			{
				done = true;
			}
			break;
		}

		if (prompt && command != 'Q')
		{
			game.Prompt();
		}
	}
}
