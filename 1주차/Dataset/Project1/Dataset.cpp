#include <iostream>
using namespace std;
void swap(int* a, int* b);
void orderset(int* arr);
void reverseSet(int* arr);
int main(void)
{
	cout << "12171856 �ֿ�� ù��° �ǽ� ����" << endl;
	int arr[10];
	int temOr[10];
	int temRe[10];
	cout << "10���� �Է°��� �־��ּ���" << endl;
	for (int i = 0; i < 10; i++)
	{
		int num;
		cin >> num;
		arr[i] = num;
	}
	for (int i = 0; i < 10; i++)
	{
		temOr[i] = arr[i];
		temRe[i] = arr[i];
	}
	orderset(temOr);
	reverseSet(temRe);
	cout << "�ּҰ�, �ִ밪 : " << temRe[0] << ", " << temOr[0] << endl;
	cout << "�������� : ";
	for (int i = 0; i < 9; i++)
	{
		cout << temRe[i] << ", ";
	}
	cout << temRe[9] << endl;
	cout << "�������� : ";
	for (int i = 0; i < 9; i++)
	{
		cout << temOr[i] << ", ";
	}
	cout << temOr[9] << endl;
}
void swap(int* a, int* b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
void orderset(int* arr)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9 - i; j++)
		{
			if (arr[j] < arr[j + 1])
			{
				swap(arr[j + 1], arr[j]);
			}
		}
	}
}
void reverseSet(int* arr)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9 - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j + 1], arr[j]);
			}
		}
	}
}