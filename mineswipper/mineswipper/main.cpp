#include <iostream>
#include "MineMap.h"
#include <string>
/*
	O O X
	X ? O
	O X O
	X - бомба
	? - флажок
	O - неизвестность
*/
int size;
int GameOn = true;

int main()
{
	while (GameOn)
	{
		std::cout << "Write field size:";
		std::cin >> size;
		MineMap test(size);
		while (test.GetLifeStatus())
		{
			system("cls");
			test.Print();
			std::string comand;
			int x;
			int y;
			bool CommandFound = false;
			while (!CommandFound)
			{
				CommandFound = true;
				std::cout << "Please write: c X Y, f X Y, u X Y for check or set/unset flag(Flags count:" << test.GetFlagsCount() << " Bombs count:" << test.GetBombsCount() << "):\n";
				std::cin >> comand >> x >> y;
				switch (comand[0])
				{
				case 'c':
				{
					test.Move(x, y);
					break;
				}
				case 'f':
				{
					test.SetFlag(x, y);
					break;
				}
				case 'u':
				{
					test.UnsetFlag(x, y);
					break;
				}
				default:
				{
					std::cout << "Wrong comand!\n";
					CommandFound = false;
					break;
				}
				}

			}
			if (test.GetWinStatus())
			{
				std::cout << "You won!\n";
			}
		};
		if (!test.GetWinStatus())
		{
			std::cout << "You lost... :(\n";
		}
		bool CommandFound = false;
		std::string comand;
		while (!CommandFound)
		{
			CommandFound = true;
			std::cout << "Do you want to continue? (Y/N)\n";
			std::cin >> comand;
			switch (comand[0])
			{
			case'Y':
			{
				break;
			}
			case 'N':
			{
				GameOn = false;
				break;
			}
			default:
			{
				std::cout << "Wrong comand!\n";
				CommandFound = false;
				break;
			}
			}
		}
	}
	return 0;
}