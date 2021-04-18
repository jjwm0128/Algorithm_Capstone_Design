#include <iostream>
using std::cout; using std::cin;  using std::endl;
void InitNext(char p[], int size);
int main()
{
	cout << "12171856 �ֿ�� �ϰ���° �ǽ� ����" << endl;
	cout << "InitNext�� AABAA ���ڿ��� ���� ���" << endl;
	char a[6] = "AABAA";
	InitNext(a, 5);
	cout << "InitNext�� ABAABAB ���ڿ��� ���� ���" << endl;
	char b[8] = "ABAABAB";
	InitNext(b, 7);
	cout << "InitNext�� ABABABAC ���ڿ��� ���� ���" << endl;
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