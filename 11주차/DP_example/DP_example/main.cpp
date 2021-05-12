#include <iostream>
using std::cout; using std::endl;

int cheese_result(int cheese[][9]);			//치즈 최대값 리턴하는 함수
int cheeseWithTrap_result(int cheese[][9]); //쥐덫이 있는조건에서 치즈 최대값 리턴하는 함수
int max(int a, int b);						//둘중 큰값을 리턴하는 함수

int main()
{
	int cheese[9][9] =
	{
		{0, 0, 1, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 1, 0, 0, 0, 0},
		{0, 1, 0, 1, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 1, 0, 0, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
	int cheeseWtihTrap[9][9] =
	{
		{0, 0, 1, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 0, 2, 0},
		{1, 0, 2, 0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 1, 2, 0, 0, 0},
		{0, 1, 0, 1, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 2, 1, 2, 0},
		{0, 1, 0, 0, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0} 
	};

	cout << cheese_result(cheese) << endl;					//예제 1 정답
	cout << cheeseWithTrap_result(cheeseWtihTrap) << endl;  //예제 2 정답
}
int cheese_result(int cheese[][9])
{
	int result[9][9] = { 0, };
	//[i][j]까지 최대 치즈값 저장하는 배열 일단 모든값 0 초기화

	if (cheese[8][0])
		result[8][0] = 1;
	//시작위치점 초기화 시작위치에 치즈가 있으면 1

	for (int i = 7; i >= 0; i--)
	{
		if (cheese[i][0] == 0)
			result[i][0] = result[i + 1][0];

		else if(cheese[i][0] == 1)
			result[i][0] = result[i + 1][0] + 1;
	}
	//맨 왼쪽 세로줄 계산 밑에꺼 + ([i][0]에 치즈가 없으면 +0 있으면 +1)

	for (int j = 1; j < 9; j++)
	{
		if (cheese[8][j] == 1)
			result[8][j] = result[8][j - 1] + 1;

		else
			result[8][j] = result[8][j - 1];
	}
	//맨 밑에 가로줄 계산 왼쪽꺼 + ([8][j]에 치즈가 없으면 +0 있으면 +1)
	//점화식 포함 안되는 예외들 처리 끝

	for (int i = 7; i >= 0; i--)
	{
		for (int j = 1; j < 9; j++)
		{
			//[i][j]까지의 치즈 최대값은 왼쪽꺼 아래꺼 비교해서 큰거 + ([i][j]에 치즈가 없으면 +0 있으면 +1)
			if (cheese[i][j] == 0)
				result[i][j] = max(result[i][j - 1], result[i + 1][j]);
			else if (cheese[i][j] == 1)
				result[i][j] = max(result[i][j - 1], result[i + 1][j]) + 1;
		}
	}

	/*
	치즈 최대값 표시 기능
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << result[i][j] << " ";
		}
		cout << endl;
	}
	*/

	return result[0][8];
	//도착지점 치즈 최대값 반환
}

int cheeseWithTrap_result(int cheese[][9])
//쥐덫이 추가됨 쥐덫구간은 -1로 바꿔주는 로직
{
	int result[9][9] = { 0, };

	if (cheese[8][0])
		result[8][0] = 1;

	for (int i = 7; i >= 0; i--)
	{
		if (cheese[i][0] == 0)
		result[i][0] = result[i + 1][0];

		else if (cheese[i][0] == 1)
			result[i][0] = result[i + 1][0] + 1;

		else if (cheese[i][0] == 2)
		{
			result[i][0] = -1;
			for (i -= 1; i >= 0; i--)
				result[i][0] = 0;
			//맨 왼쪽 세로줄 중간에 쥐덫이 있으면 쥐덫 있는데는 -1 쥐덫 이후는 갈방법이 없으므로 0표시
		}
	}

	for (int j = 1; j < 9; j++)
	{
		if (cheese[8][j] == 0)
			result[8][j] = result[8][j - 1];

		else if (cheese[8][j] == 1)
			result[8][j] = result[8][j - 1] + 1;

		else if (cheese[8][j] == 2)
		{
			result[8][j] = -1;
			for (j += 1; j < 9; j++)
				result[8][j] = 0;
			//맨 밑에 가로줄 중간에 쥐덫이 있으면 쥐덫 있는데는 -1 쥐덫 이후는 갈방법이 없으므로 0표시
		}
	}

	
	for (int i = 7; i >= 0; i--)
	{
		for (int j = 1; j < 9; j++)
		{
			//[i][j]까지의 치즈 최대값은 왼쪽꺼 아래꺼 비교해서 큰거 + ([i][j]에 치즈가 없으면 +0 있으면 +1)
			//[i][j]에 쥐덫이 있으면 -1처리해서 지나갈수 없음
			if (cheese[i][j] == 0)
				result[i][j] = max(result[i][j - 1], result[i + 1][j]);

			else if (cheese[i][j] == 1)
				result[i][j] = max(result[i][j - 1], result[i + 1][j]) + 1;

			else if (cheese[i][j] == 2)
				result[i][j] = -1;
		}
	}

	/*
	치즈 최대값 표시 기능
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << result[i][j] << " ";
		}
		cout << endl;
	}
	*/

	return result[0][8];
}

int max(int a, int b)
{
	if (a >= b)
		return a;
	else
		return b;
}