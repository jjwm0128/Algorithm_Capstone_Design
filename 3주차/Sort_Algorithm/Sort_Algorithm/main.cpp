#include <iostream>
#include <ctime>
using namespace std;
void checkSort(int a[], int n);
void MergeSort(int size, int* arr);
void Merge(int h, int m, int* x1, int* x2, int* arr);
void SelectionSort(int size, int* arr);
int main()
{
	cout << "12171856 �ֿ�� ����° �ǽ� ����" << endl;
	cout << "10���� ���� ����� ���ĵǴ��� Ȯ��" << endl << "10���� ���� �Է��Ͻÿ�" << endl;
	int arrA[10];
	int temA[10];
	int temB[10];
	for (int i = 0; i < 10; i++)
	{
		int num;
		cin >> num;
		arrA[i] = num;
		temA[i] = num;
		temB[i] = num;
	}
	cout << "���� �Ǳ� ���� ���� �迭" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << arrA[i] << "  ";
	}
	cout << endl;
	MergeSort(10, temA);
	cout << "Merge sort�� ���� ���� ���� �迭" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << temA[i] << "  ";
	}
	cout << endl;
	SelectionSort(10, temB);
	cout << "Selection sort�� ���� ���� ���� �迭" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << temB[i] << "  ";
	}
	cout << endl;
	cout << "�̹��� 10������ ���� ���� �����Ҷ��� �ð� ��" << endl;
	clock_t Merge_start, Merge_end;
	clock_t Selection_start, Selection_end;
	float Merge_res, Selection_res;
	int arrB[100000];
	int temC[100000];
	int temD[100000];
	srand(time(NULL));
	for (int i = 0; i < 100000; i++)
	{
		arrB[i] = rand() % 100000;
		temC[i] = arrB[i];
		temD[i] = arrB[i];
	}
	Merge_start = clock();
	MergeSort(100000,temC);
	Merge_end = clock();
	Selection_start = clock();
	SelectionSort(100000,temD);
	Selection_end = clock();
	Merge_res = (float)(Merge_end - Merge_start);
	Selection_res = (float)(Selection_end - Selection_start);
	cout << "Merge sort �ҿ� �ð� = " << Merge_res << "ms" << endl;
	cout << "Selection Sort �ҿ� �ð� = " << Selection_res << "ms" << endl;
	checkSort(temC, 100000);
	checkSort(temD, 100000);
}
void checkSort(int a[], int n)
//���� �����̹Ƿ� üũ��Ʈ�� �ܼ��� �迭 ũ�⸸ŭ �����鼭 i��° ���� i+1��° ������ �۰ų� ������ sorted�� true ũ�� false
//������ �´� �޼��� ���
{
	int i;
	bool sorted;
	sorted = true;
	for (i = 0; i < n-1; i++) {
		if (a[i] > a[i + 1]) {
			sorted = false;
		}
		if (!sorted) {
			break;
		}
	}
	if (sorted) {
		printf("Sorting complete!\n");
	}
	else {
		printf("Error during sorting...\n");
	}
}
void MergeSort(int size, int* arr)
//�պ� ������ ������ �迭�� �ϳ��� ���� ���������� ��� �п��ؼ�
//�п��� �迭���� ���ؼ� ��迭�Ѵ�
{
	{
		int n = size;
		// ���Ӱ� �迭�� ������ �ϴµ� ��ũ��� ���� �迭�� ũ��� ����
		if (n > 1)
		{
			int h = n / 2;
			int m = n - h;
			//�迭�� �κз��� ������ �ϴ� h�� m�� �̷��� ����
			int* x1 = new int[h];
			int* x2 = new int[m];
			//hũ���� int�迭 x1 ����
			//mũ���� int�迭 x2 ����
			for (int i = 0; i <= h - 1; i++)
			{
				x1[i] = arr[i];
			}
			//�迭 �պκп� �ִ°͵��� x1�� ���
			for (int i = 0; i <= m - 1; i++)
			{
				x2[i] = arr[i + h];
			}
			//�迭 �޺κп� �ִ°͵��� x2�� ��´�
			MergeSort(h, x1);
			//�պκ��� ���� �͵��� �� �п���Ų��
			//����Լ��̹Ƿ� n<=1�� �ɶ� ���� �п�
			MergeSort(m, x2);
			//�޺κ��� ���� �͵鵵 ��������
			Merge(h, m, x1, x2, arr);
			//���� �п��� �迭���� ���ǿ� ���� �ٽ� ��ģ��
		}
	}
}
void Merge(int h, int m, int* x1, int* x2, int* arr)
//�п��� �迭���� ��ġ�� �˰���
{
	int i, j, k;
	i = 0;
	j = 0;
	k = 0;
	while (i <= h - 1 && j <= m - 1)
		//i�� j�� Ŀ���� h-1�̳� m-1�� �Ǹ� ��� �� �迭�� ���� ������ �迭�� ���ٴ� �ǹ�
		//���� ������ �� �迭�� �ִ°� while�� �ۿ� �д�
	{
		if (x1[i] <= x2[j])
			//x1�迭�� x2�迭�� ���ؼ� �������� �����ͺ��� �ΰ��� ��ĥ �迭�� ��
			//�׸��� �� �������� ������ �迭�� �տ� ���� ���ο������ �����Ƿ� ++���ش�
		{
			arr[k] = x1[i];
			i++;
		}
		else
		{
			arr[k] = x2[j];
			j++;
		}
		k++;
		//���ο� �迭�� �������� k++
	}
	//i�� j�� Ŀ���� h-1�̳� m-1�� ��� �� �迭�� ���� ������ �迭�� ���� ������ �� �迭�� ������ �迭�� �ڷ� ������ ��
	if (i > h - 1)
		//x1 �迭�� �ִ� ������ ��� �� �迭�� ����
	{
		for (j; j <= m - 1; j++)
		{
			arr[k] = x2[j];
			k++;
			//x2�迭�� ���� ������ ���迭�� �ڷ� ���Ե�
		}
	}
	else
	{
		for (i; i <= h - 1; i++)
		{
			arr[k] = x1[i];
			k++;
		}
		//�ݴ��� ��� ��������
	}
	delete[] x1;
	delete[] x2;
	//x1 x2�� ��� ���迭�� �־����Ƿ� delete���ش�
	//�Լ� mergesort���� logn ��ŭ merge���� n��ŭ �ð����⵵�̹Ƿ�
	//�ᱹ mergesort �˰����� �ð����⵵�� O(nlogn)
}
void SelectionSort(int size, int* arr)
//selection sort�� ������ ���� �ּҰ��̶� ���� �迭�� �� scan�ϸ鼭 ���� �ּҰ��̶� �ڸ�����
{
	for (int i = 0; i < size; i++)
	{
		int nth = i;
		for (int j = i + 1; j < size; j++)
			//�迭�� �� ��ĵ�ϴٰ�
		{
			if (arr[j] < arr[nth])
				//�迭 ������ ������(j��°�� ����)�� �߰��ϸ� nth�� j�� �ٲ��(�� ���� j��° ���̶� ��) ��� ��ĵ
			{
				nth = j;
			}
			//���⸦ ������ ù��° ���� �� ������ �迭 ������ �ּҰ��� ã�Ƴ��� 
		}
		int temp = arr[nth];
		arr[nth] = arr[i];
		arr[i] = temp;
		//ù��° ���� �迭�� �ּҰ��� ���� �ڸ� �̵�
	}
	//�̰Ÿ� �迭 �����ִ� ���ڱ��� ��� ����
	//��Ƚ���� (n-1) + (n-2)....+1 -> n(n-1)/2 
	//�ᱹ selection sort �˰����� �ð����⵵�� O(n^2)
}