#include <iostream>
#include <ctime>
using namespace std;
void QuickSort(int a[], int l, int r);
void swap(int a[], int b, int c);
void checkSort(int a[], int n);
int main()
{
	cout << "12171856 �ֿ�� �׹�° �ǽ� ����" << endl;
	cout << "10���� ���� ����� ���ĵǴ��� Ȯ��" << endl << "10���� ���� �Է��Ͻÿ�" << endl;
	int arrA[10];
	int temA[10];
	for (int i = 0; i < 10; i++)
	{
		int num;
		cin >> num;
		arrA[i] = num;
		temA[i] = num;
	}
	//10�� �� �ް� �װ� �迭�� �ִ´�. �� �迭�� ��ġ�� �ʱ����� ���迭 �����Ѱ��� �����غ����� temA�� ����� arrA���� ����
	cout << "���� �Ǳ� ���� ���� �迭" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << arrA[i] << "  ";
	}
	cout << endl;
	//���ĵǱ� �� �迭 ���
	QuickSort(temA,0,9);
	//����Ʈ ����
	cout << "Merge sort�� ���� ���� ���� �迭" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << temA[i] << "  ";
	}
	//�迭�� ���� �� �Ƴ� Ȯ��
	cout << endl;
	cout << "10������ ���� quick sort�Ҷ� �ҿ�ð�" << endl;
	clock_t Quick_start, Quick_end;
	float Quick_res;
	int arrB[100000];
	int temB[100000];
	srand(time(NULL));
	for (int i = 0; i < 100000; i++)
	{
		arrB[i] = rand() % 100000;
		temB[i] = arrB[i];
	}
	//�̹��� 10������ ���� �� �迭 
	//srand rand�Լ� �Ἥ �����ϰ� 10������ �� �ְ� ���� �����ϰ� �迭 �ϳ� �� ����� ����
	Quick_start = clock();
	QuickSort(temB,0,99999);
	Quick_end = clock();
	Quick_res = (float)(Quick_end - Quick_start);
	cout << "Quick sort �ҿ� �ð� = " << Quick_res << "ms" << endl;
	//����Ʈ ������ �ҿ�ð� ���
	checkSort(temB, 100000);
	//10�� ũ���� �迭�� �� ���ĵǾ��� Ȯ��
}
void QuickSort(int a[], int l, int r)
//����Ʈ ����
{
	int i, j, m, v;
	if (r - l > 1) 
	//�ɰ��� �迭���� ������ 3�� �̻��̸�
	{
		m = (l + r) / 2;
		//m�� l�� r�� �߰���
		if (a[l] > a[m]) swap(a, l, m);
		if (a[l] > a[r]) swap(a, l, r);
		if (a[m] > a[r]) swap(a, m, r);
		//�ϴ� ù��°, �߰���°, ������ ���ڸ� ���ؼ� �����Ѵ�.
		swap(a, m, r - 1);
		//ù��° �߰���° ������ ���ڴ� ���ĵǾ������Ƿ� m��° ���� �Ǻ����� ���Ұ��̹Ƿ� �Ǻ��� ������ -1��° ���ڸ� �ϴ� �ٲ��ְ�
		v = a[r - 1]; i = l; j = r - 1;
		//�ؿ��� ���� �����ڸ� ����Ұ� �̹Ƿ� i��ù��° j�� �Ǻ��̶� ����
		for (; ; ) {
			while (a[++i] < v);
			//ó�� while�������� �ι�°������ �Ǻ��̶� ��
			//�Ǻ����� ū ���� ��ĵ�ϸ� while�� ��������
			while (a[--j] > v);
			//ó�� while�������� �Ǻ� �����̶� ��
			//�Ǻ����� ���� ���� ��ĵ�ϸ� while�� ��������
			if (i >= j) break;
			//���࿡ i>=j��� �� i�� j�� �����ϸ� �Ǻ� �ڸ��� ã���Ŵϱ� for�� ��������
			swap(a, i, j);
			//�������� �ʾ����� ��ĵ�� �μ� �ٲٱ�
		}
		swap(a, i, r - 1);
		//�Ǻ� �ڸ� i�� ã�����Ƿ� �Ǻ��ڸ��� �Ǻ��� ��ġ��Ű��
		QuickSort(a, l, i - 1);
		//�Ǻ� ������ ����Ʈ ������
		QuickSort(a, i + 1, r);
		//�Ǻ� �������� ����Ʈ ������
	}
	else if (a[l] > a[r]) swap(a, l, r);
	//�迭���� ������ 2�� ���ϸ� �׳� �� �μ��� ���ؼ� ����
}
void swap(int a[], int b, int c)
//������ �����Լ�
{
	int temp;
	temp = a[b];
	a[b] = a[c];
	a[c] = temp;
}
void checkSort(int a[], int n)
//���� �����̹Ƿ� üũ��Ʈ�� �ܼ��� �迭 ũ�⸸ŭ �����鼭 i��° ���� i+1��° ������ �۰ų� ������ sorted�� true ũ�� false
//������ �´� �޼��� ���
{
	int i;
	bool sorted;
	sorted = true;
	for (i = 0; i < n - 1; i++) {
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