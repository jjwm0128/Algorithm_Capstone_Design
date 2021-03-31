#include <iostream>
#include <ctime>
using std::cout; using std::cin; using std::endl;
void checkSort(int a[], int n);
void max_heapify(int a[], int h, int m);
void max_HeapSort(int a[], int n);
void checkSort_R(int a[], int n);
void min_heapify(int a[], int parent, int size);
void min_HeapSort(int a[], int n);
//checkSort_R�̶� minheap�� �̿��Ѱ� checkSort�� maxheap���� �� ���Ҷ� ��ȣ�� �ݴ�� ���ָ� �ǹǷ�
//minheap�� ���� ����
int main()
{
	cout << "12171856 �ֿ�� �ټ���° �ǽ� ����" << endl;
	cout << "10���� ���� ����� ���ĵǴ��� Ȯ��" << endl << "10���� ���� �Է��Ͻÿ�" << endl;
	int arrA[11];
	int temA[11];
	int temB[11];
	//heap�� 1���� �����ϸ� �θ�*2 = left  �θ�*2 +1= right �̷��� �ļ���� ���ϴ�
	//���� 0���� ���� 1 10���� �������� ���ϴ� ũ�� +1 ��ŭ �迭 ����
	arrA[0] = -1;
	temA[0] = -1;
	temB[0] = -1;
	//0���� �ϴ� -1�� �ʱ�ȭ ��Ų��. (0���� �ƿ� �˰��� ���� ��������� �ƴϹǷ� �׳� �ܼ��� �ʱ�ȭ ��Ű�� �뵵)
	//�׷��� ���� for���� �� 1�ν��� �ǵ��� ũ���°���� ����
	for (int i = 1; i < 11; i++)
	{
		int num;
		cin >> num;
		arrA[i] = num;
		temA[i] = num;
		temB[i] = num;
	}
	cout << "���� �Ǳ� ���� ���� �迭" << endl;
	for (int i = 1; i < 11; i++)
	{
		cout << arrA[i] << "  ";
	}
	cout << endl;
	max_HeapSort(temA,10);
	cout << "MaxHeap sort�� ���� ���� ���� �迭(�����迭)" << endl;
	for (int i = 1; i < 11; i++)
	{
		cout << temA[i] << "  ";
	}
	cout << endl;
	
	min_HeapSort(temB,10);
	cout << "MinHeap sort�� ���� ���� ���� �迭(�����迭)" << endl;
	for (int i = 1; i < 11; i++)
	{
		cout << temB[i] << "  ";
	}
	cout << endl;
	
	cout << "�̹��� 10������ ���� ���� �����Ҷ��� �ð� ��" << endl;
	clock_t Max_start, Max_end;
	clock_t Min_start, Min_end;
	float Max_res, Min_res;
	int arrB[100001];
	int temC[100001];
	int temD[100001];
	//10���� �����ϰ� +1��ŭ �迭 ����
	arrB[0] = -1;
	temC[0] = -1;
	temD[0] = -1;
	srand(time(NULL));
	for (int i = 1; i < 100001; i++)
	{
		arrB[i] = rand() % 100000;
		temC[i] = arrB[i];
		temD[i] = arrB[i];
	}
	Max_start = clock();
	max_HeapSort(temC,100000);
	Max_end = clock();
	Min_start = clock();
	min_HeapSort(temD, 100000);
	Min_end = clock();
	Max_res = (float)(Max_end - Max_start);
	Min_res = (float)(Min_end - Min_start);
	cout << "MaxHeap sort �ҿ� �ð� = " << Max_res << "ms" << endl;
	cout << "MinHeap Sort �ҿ� �ð� = " << Min_res << "ms" << endl;
	//�ð� ���
	checkSort(temC, 100000);
	//maxheap�� �����Ѱ� checksort�� Ȯ��
	checkSort_R(temD, 100000);
	//minheap�� �����Ѱ� checksort_R�� Ȯ��
}
void checkSort(int a[], int n)
//���� �����̹Ƿ� üũ��Ʈ�� �ܼ��� �迭 ũ�⸸ŭ �����鼭 i��° ���� i+1��° ������ �۰ų� ������ sorted�� true ũ�� false
//������ �´� �޼��� ���
//�����̶� �޶����� ������ 0���� n-2���� �� �̹����� 1������ �迭 �����̹Ƿ� 1���� n-1���� ��
{
	int i;
	bool sorted;
	sorted = true;
	for (i = 1; i < n; i++) {
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
void max_heapify(int a[], int parent, int size)
{
	int v = a[parent];
	//�ϴ� �θ����� ���� ���� �����صΰ�
	int j;
	for (j = 2 * parent; j <= size; j = 2 * j)
		//*2���ϸ� left�� ���� �ȴ� �� �Ʒ��� ��� �������鼭 ��
		//j>size�� �Ʒ��� �� ���鼭 �����Ѱ� 
	{
		if (j < size && a[j] < a[j + 1])
			//j<size�� ������ ������ ������ ū�� ã��
		{
			j = j + 1;
		}
		//������ ū���� j����
		if (v >= a[j])
		//������ ū���̶� �θ�� ��
		{
			break;
		//�θ� ũ�ų� ������ �ٲ� �ʿ䰡 ������ �״�� for�� �����
		}
		else
		{
			a[j / 2] = a[j]; // �θ� ������ a[j]�� �θ� ���� �̵�
		}
	}
	a[j / 2] = v;
	//�θ� ũ�� �״�� �θ��� �ٽ� �θ��忡 ����
	//�θ� ������ j�� 2�谡 �Ǿ� �θ��� ���� �ڽĳ�忡 ���Եȴ�.
}
void max_HeapSort(int a[], int n)
{
	int i, temp;
	for (i =n / 2; i >= 1; i--)  // �迭 a[]�� ������ ��ȯ
	{
		max_heapify(a, i, n); //���� ���� heap�� �迭�� �� ���Ҽ�/2 ��ŭ�� ����heap�� �ִٰ� �����ϸ� ��
		//�׸��� �Ʒ��ſ������� ���Ұ��̹Ƿ� 1���� n/2����
	}
	for (i = n-1 ; i >= 1; i--)
	{ // �迭 a[]�� ������������ ����
		temp = a[1]; //max heap�̹Ƿ� a[1]�� ���� ū ����
		a[1] = a[i + 1]; // a[1]�� ���ĵ��� ���� ���� ���� ���� ��ü
		a[i + 1] = temp;//���� ���� ���Ұ� ���� ū ���ҷ� �� ���� ���� ������ ���Ҵ� ���ĵ� ����
		max_heapify(a, 1, i); //�̰� n����ŭ �ݺ� 
	}
}
void checkSort_R(int a[], int n)
{
	int i;
	bool sorted;
	sorted = true;
	for (i = 1; i < n ; i++) {
		if (a[i] < a[i + 1]) {
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
void min_heapify(int a[], int parent, int size)
{
	int v = a[parent];
	int j;
	for (j = 2 * parent; j <= size; j = 2 * j)
	{
		if (j < size && a[j] > a[j + 1])
		{
			j = j + 1;
		}
		if (v <= a[j])
		{
			break;
		}
		else
		{
			a[j / 2] = a[j];
		}
	}
	a[j / 2] = v;
}
void min_HeapSort(int a[], int n)
{
	int i, temp;
	for (i = n / 2; i >= 1; i--)  
	{
		min_heapify(a, i, n); 
	}
	for (i = n - 1; i >= 1; i--)
	{ 
		temp = a[1];
		a[1] = a[i + 1]; 
		a[i + 1] = temp;
		min_heapify(a, 1, i);
	}
}
