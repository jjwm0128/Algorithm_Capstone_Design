#include <iostream>
#include <ctime>
using namespace std;
void Cubic_Complexity(int a);
int Exponential_Complexity(int a);
int main(void)
{
	cout << "12171856 주우민 두번째 실습 과제" << endl;
	clock_t Cubic_start, Cubic_end;
	clock_t Expo_start, Expo_end;
	float Cubic_res, Expo_res;
	int Cubic_input, Exponential_input;
	cout << "Cubic complexity 알고리즘 입력값을 넣으시오" << endl;
	cin >> Cubic_input;
	cout << "Exponential complexity 알고리즘 입력값을 넣으시오" << endl;
	cin >> Exponential_input;
	Cubic_start = clock();
	Cubic_Complexity(Cubic_input);
	Cubic_end = clock();
	Expo_start = clock();
	Exponential_Complexity(Exponential_input);
	Expo_end = clock();
	Cubic_res = (float)(Cubic_end - Cubic_start);
	Expo_res = (float)(Expo_end - Expo_start);
	cout << "n^3(Cubic complexity) 소요 시간 = " << Cubic_res << "ms" << endl;
	cout << "2^n(Exponential complexity) 소요 시간 = " << Expo_res << "ms" << endl;
}
void Cubic_Complexity(int a)
{
	int** arrayA = new int* [a];
	int** arrayB = new int* [a];
	int** arrayC = new int* [a];
	int** arrayD = new int* [a];
	int** arrayE = new int* [a];
	for (int i = 0; i < a; i++)
	{
		arrayA[i] = new int[a];
		arrayB[i] = new int[a];
		arrayC[i] = new int[a];
		arrayD[i] = new int[a];
		arrayE[i] = new int[a];
	}
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < a; j++)
		{
			arrayA[i][j] = 1;
			arrayB[i][j] = 1;
			arrayC[i][j] = 1;
			arrayD[i][j] = 1;
			arrayE[i][j] = 1;
		}
	}
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < a; j++)
		{
			for (int k = 0; k < a; k++)
			{
				arrayD[i][j] += arrayA[i][k] + arrayB[k][j];
			}
		}
	}
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < a; j++)
		{
			for (int k = 0; k < a; k++)
			{
				arrayE[i][j] += arrayC[i][k] + arrayD[k][j];
			}
		}
	}
	for (int i = 0; i < a; i++)
	{
		delete[] arrayA[i];
		delete[] arrayB[i];
		delete[] arrayC[i];
		delete[] arrayD[i];
		delete[] arrayE[i];
	}
	delete[] arrayA;
	delete[] arrayB;
	delete[] arrayC;
	delete[] arrayD;
	delete[] arrayE;
}
int Exponential_Complexity(int a)
{
	if (a < 2)
	{
		return a;
	}
	else
	{
		return Exponential_Complexity(a - 1) + Exponential_Complexity(a - 2);
	}
}