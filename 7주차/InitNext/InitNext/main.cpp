#include <iostream>
using std::cout; using std::cin;  using std::endl;
void InitNext(char p[], int size);
int main()
{
	cout << "12171856 주우민 일곱번째 실습 과제" << endl;
	cout << "InitNext에 AABAA 문자열을 넣은 결과" << endl;
	char a[6] = "AABAA";
	InitNext(a, 5);
	cout << "InitNext에 ABAABAB 문자열을 넣은 결과" << endl;
	char b[8] = "ABAABAB";
	InitNext(b, 7);
	cout << "InitNext에 ABABABAC 문자열을 넣은 결과" << endl;
	char c[9] = "ABABABAC";
	InitNext(c, 8);
}
void InitNext(char p[], int size)
{
	int m = size;
	int* next = new int[m];
	next[0] = -1;
	for (int i = 0, j = -1; i < m; i++, j++)
	{

		if (p[i] == p[j])
		{
			next[i] = next[j];
		}
		else
		{
			next[i] = j;
		}
		while (j >= 0 && p[i] != p[j])
		{
			j = next[j];
		}
	}
	for (int i = 1; i < m; i++)
	{
		cout << next[i] << "  ";
	}
	cout << endl;
	delete[] next;
}