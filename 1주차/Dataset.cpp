#include <iostream>
using namespace std;
void orderset(int* temp)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9 - i; j++)
		{
			if (temp[j] < temp[j + 1])
			{
				swap(temp[j + 1], temp[j]);
			}
		}
	}
	cout << "�������� : ";
	for (int i = 0; i < 10; i++)
	{
		cout << temp[i] << "  ";
	}
	cout << endl;
}
void reverseSet(int array[])
{
	int temp[10];
	for (int i = 0; i < 10; i++)
	{
		temp[i] = array[i];
	}
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9 - i; j++)
		{
			if (temp[j] > temp[j + 1])
			{
				swap(temp[j + 1], temp[j]);
			}
		}
	}
	/*cout << "�������� : ";
	for (int i = 0; i < 10; i++)
	{
		cout << temp[i] << "  ";
	}
	cout << "�ּҰ�, �ִ밪 " << temp[0] << "  " << temp[9] << endl;
	cout << endl;*/
}
void swap(int* a, int* b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
int main(void)
{
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
	for (int i = 0; i < 10; i++)
	{
		cout << temOr[i] << "  ";
	}
	cout << endl;
	//cout << "12171856 �ֿ�� ù��° �ǽ� ����" << endl;
}