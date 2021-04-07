#include <iostream>
using std::cout; using std::cin;  using std::endl;
void Radix_Sort(int* data, int size, int p, int k);
int main()
{
	cout << "12171856 �ֿ�� ������° �ǽ� ����" << endl;
	cout << "8���� ���� ����� ���ĵǴ��� Ȯ��" << endl << "8���� ���� �Է��Ͻÿ�" << endl;
	int* arrA = new int[8];
	int* temA = new int[8];
	for (int i = 0; i < 8; i++)
	{
		int num;
		cin >> num;
		arrA[i] = num;
		temA[i] = num;
	}
	//8�� �� �ް� �װ� �迭�� �ִ´�. �� �迭�� ��ġ�� �ʱ����� ���迭 �����Ѱ��� �����غ����� temA�� ����� arrA���� ����
	cout << "���� �Ǳ� ���� ���� �迭" << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << arrA[i] << "  ";
	}
	cout << endl;
	//���ĵǱ� �� �迭 ���
	Radix_Sort(temA, 8, 100, 10);
	//Radix ��Ʈ ����
	cout << "Radix sort�� ���� ���� ���� �迭" << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << temA[i] << "  ";
	}
	//�迭�� ���� �� �Ƴ� Ȯ��
	cout << endl;
	delete[] arrA;
	delete[] temA;
}
/**
  * @data  ���� �迭
  * @size  data�� �������� ����
  * @p  ������ �ִ� �ڸ���
  * @k  ���(10������ ����Ѵٸ� 10)

  */
void Radix_Sort(int* data, int size, int p, int k) 
{
	int* counts; // Ư�� �ڸ����� ���ڵ��� ī��Ʈ
	int* temp; // ���ĵ� �迭�� ���� �ӽ� ���
	int index, pval, i, j, n;
	// �޸� �Ҵ�
	if ((counts = new int[k]) == NULL)
		return;
	if ((temp = new int[size]) == NULL)
		return;
	for (n = 0; n < p; n++) 
	{ // 1�� �ڸ�, 10���ڸ�, 100�� �ڸ� ������ ����
		for (i = 0; i < k; i++)
		{
			counts[i] = 0; // �ʱ�ȭ
		   // ��ġ�� ���.
		  // n:0 => 1,  1 => 10, 2 => 100
		}
		pval = (int)pow((double)k, (double)n);
		// �� ������ �߻�Ƚ���� ����.
		for (j = 0; j < size; j++) 
		{
			// 253�̶�� ���ڶ��
			// n:0 => 3,  1 => 5, 2 => 2
			index = (int)(data[j] / pval) % k;
			counts[index] = counts[index] + 1;
		}
		// ī��Ʈ �������� ���Ѵ�. ��������� ���ؼ�.
		for (i = 1; i < k; i++) 
		{
			counts[i] = counts[i] + counts[i - 1];
		}
		// ī��Ʈ�� ����� �� �׸��� ��ġ�� �����Ѵ�.
		// ������� ���
		for (j = size - 1; j >= 0; j--) 
		{ // �ڿ������� ����
			index = (int)(data[j] / pval) % k;
			temp[counts[index] - 1] = data[j];
			counts[index] = counts[index] - 1; // �ش� ���� ī��Ʈ�� 1 ����
		}
		// �ӽ� ������ ����
		memcpy(data, temp, size * sizeof(int));
	}
	delete[] counts;
	delete[] temp;
}