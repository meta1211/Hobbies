#include "MineMap.h"
#include <ctime>
#include <cstdlib>
#include <limits>
#include <iostream>

template<typename T>
T** MineMap::CreateArray(T type, int x, int y)
{
	T **a = new T*[x];
	for (int i = 0; i < x; i++)
	{
		a[i] = new T[y];
	}
	return a;
}

template <typename T>
T** MineMap::CreateArray(T type, int x)
{
	T **a = new T*[x];
	for (int i = 0; i < x; i++)
	{
		a[i] = new T[x];
	}
	return a;
}

void MineMap::GenerateMineField(int size)
{
	delete[] MineField;
	MineField = CreateArray(' ', size);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			MineField[i][j] = 'O';
		}
	}
}

void MineMap::GenerateBombs(int size, double bombsCount)
{
	delete[] FlagsAndBombs;
	FlagsAndBombs = CreateArray(0 ,size);
	//srand(clock());
	int curentCount = 0;
	for (int i = 0; i < bombsCount; i++)
	{
		int x = rand() % size;
		int y = rand() % size;
		while (FlagsAndBombs[x][y] == FieldsType::bomb)
		{
			x = rand() % size;
			y = rand() % size;
		}
		FlagsAndBombs[x][y] = FieldsType::bomb;
	}
}

void MineMap::GenerateRevealedFields(int size)
{
	delete[] RevealedFields;
	RevealedFields = CreateArray(false, size);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			RevealedFields[i][j] = false;
		}
	}
}

void MineMap::ResetFields()
{
	GenerateMineField(Size);
	GenerateBombs(Size, bombsCount);
	GenerateRevealedFields(Size);
}

void MineMap::Print()
{
	std::cout << "Mine field:\n";
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			std::cout << MineField[i][j] << ' ';
		}
		std::cout << '\n';
	}
	std::cout << '\n';

	//std::cout << "Flags and bombs:\n";
	//for (int i = 0; i < Size; i++)
	//{
	//	for (int j = 0; j < Size; j++)
	//	{
	//		std::cout << FlagsAndBombs[i][j] << ' ';
	//	}
	//	std::cout << '\n';
	//}
	//std::cout << '\n';

	//std::cout << "Revealed fields:\n";
	//for (int i = 0; i < Size; i++)
	//{
	//	for (int j = 0; j < Size; j++)
	//	{
	//		std::cout << RevealedFields[i][j] << ' ';
	//	}
	//	std::cout << '\n';
	//}
	//std::cout << '\n';
}
	
void MineMap::Move(int x , int y)
{
	if (OutOfBounds(x, y))
	{
		OutOfBoundsMessage();
	}
	else if (FlagsAndBombs[x][y] == FieldsType::bomb)
	{
		LifeStatus = false;
	}
	else if (FlagsAndBombs[x][y] == FieldsType::flag || FlagsAndBombs[x][y] == FieldsType::flagAndBomb)
	{
		std::cout << "You can't check zones with flag!";
	}
	else
	{
		Check(x, y);
	}
}

void MineMap::SetFlag(int x, int y)
{
	if (!OutOfBounds(x, y))
	{
		if (RevealedFields[x][y] == false)
		{
			FlagsCount++;
			MineField[x][y] = 'F';
			if (IsBomb(x, y))
			{
				FlagsAndBombs[x][y] = FieldsType::flagAndBomb;
				CorrectFlagsCount++;
				if (CorrectFlagsCount == bombsCount && FlagsCount == CorrectFlagsCount)
				{
					WinStatus = true;
					LifeStatus = false;
				}
			}
			else
			{
				FlagsAndBombs[x][y] = FieldsType::flag;
			}
		}
		else
		{
			std::cout << "You cant flag revealed fields!\n";
		}
	}
	else
	{
		OutOfBoundsMessage();
	}
}

void MineMap::UnsetFlag(int x, int y)
{
	if (!OutOfBounds(x, y))
	{
		if (MineField[x][y] == 'F')
		{
			MineField[x][y] = 'O'; 
			FlagsCount--;
			if (IsBomb(x, y))
			{
				CorrectFlagsCount--;
			}
		}
		else
		{
			std::cout << "There is no flag!\n";
		}
	}
	else
	{
		OutOfBoundsMessage();
	}
}

bool MineMap::IsBomb(int x, int y)
{
	return FlagsAndBombs[x][y] == FieldsType::bomb || FlagsAndBombs[x][y] == FieldsType::flagAndBomb;
}

bool MineMap::OutOfBounds(int x, int y)
{
	return x < 0 || x > Size - 1 || y < 0 || y > Size - 1;
}

void MineMap::OutOfBoundsMessage()
{
	std::cout << "Wrong coordinates!\n";
}

int MineMap::NearBombsCount(int x, int y)
{
	int count = 0;
	for (int dX = -1; dX < 2; dX++)
	{
		for (int dY = -1; dY < 2; dY++)
		{
			if (!OutOfBounds( x - dX,  y - dY) && IsBomb(x - dX, y - dY))
			{
				count++;
			}
		}
	}
	return count;
}

void MineMap::Check(int x, int y)
{
	if (OutOfBounds(x, y) || RevealedFields[x][y] || IsBomb(x, y))
	{
		return;
	}
	int count = NearBombsCount(x, y);
	RevealedFields[x][y] = true;
	if (count > 0)
	{
		MineField[x][y] = (char)(count + '0');
	}
	else
	{
		MineField[x][y] = 'X';
	}
	/*
	Call scheme:
	0 C 0
	C x C
	0 C 0
	*/
	Check(x - 1, y);
	Check(x , y + 1);
	Check(x + 1, y);
	Check(x, y - 1);
}

MineMap::MineMap(int size)
{
	LifeStatus = true;
	WinStatus = false;
	FlagsCount = 0;
	CorrectFlagsCount = 0;
	Size = size;
	bombsCount = (int)(((double)(size * size)) / 4) + 1;
	GenerateMineField(size);
	GenerateBombs(size, bombsCount);
	GenerateRevealedFields(size);
}

MineMap::~MineMap()
{
	for (int i = 0; i < Size; i++)
	{
		delete[]MineField[i];
		delete[]FlagsAndBombs[i];
		delete[]RevealedFields[i];
	}
	delete[]MineField;
	delete[]FlagsAndBombs;
	delete[]RevealedFields;
}
