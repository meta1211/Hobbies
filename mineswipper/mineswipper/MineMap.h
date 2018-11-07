#pragma once
class MineMap
{
	static enum FieldsType
	{
		flagAndBomb = -1,
		empty,
		bomb,
		flag
	};

	char **MineField;
	int **FlagsAndBombs;
	bool **RevealedFields;
	int Size;
	bool LifeStatus;
	bool WinStatus;
	int CorrectFlagsCount;
	int FlagsCount;
	int bombsCount;

	template<typename T>
	T** CreateArray(T, int, int);
	template<typename T>
	T** CreateArray(T, int);
	bool OutOfBounds(int, int);
	void OutOfBoundsMessage();
	void GenerateMineField(int);
	void GenerateBombs(int, double);
	void GenerateRevealedFields(int);
	int NearBombsCount(int, int);
	void Check(int, int);
	bool IsBomb(int, int);

public:
	void ResetFields();
	void Print();
	void Move(int, int);
	void SetFlag(int, int);
	void UnsetFlag(int, int);

	bool GetLifeStatus()
	{
		return LifeStatus;
	}
	bool GetWinStatus()
	{
		return WinStatus;
	}
	int GetFlagsCount()
	{
		return FlagsCount;
	}
	int GetCorrectFlagsCount()
	{
		return CorrectFlagsCount;
	}
	int GetBombsCount()
	{
		return bombsCount;
	}
	MineMap(int size = 3);
	~MineMap();
};

