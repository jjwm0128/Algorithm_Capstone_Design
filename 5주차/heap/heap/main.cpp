#include <iostream>
#include <ctime>
using std::cout; using std::cin; using std::endl;
void checkSort(int a[], int n);
void max_heapify(int a[], int h, int m);
void max_HeapSort(int a[], int n);
void checkSort_R(int a[], int n);
void min_heapify(int a[], int parent, int size);
void min_HeapSort(int a[], int n);
//checkSort_R이랑 minheap을 이용한건 checkSort랑 maxheap에서 값 비교할때 부호만 반대로 해주면 되므로
//minheap은 설명 생략
int main()
{
	cout << "12171856 주우민 다섯번째 실습 과제" << endl;
	cout << "10개의 수가 제대로 정렬되는지 확인" << endl << "10개의 수를 입력하시오" << endl;
	int arrA[11];
	int temA[11];
	int temB[11];
	//heap은 1부터 시작하면 부모*2 = left  부모*2 +1= right 이렇게 식세우기 편하다
	//따라서 0번을 비우고 1 10까지 쓰기위해 원하던 크기 +1 만큼 배열 생성
	arrA[0] = -1;
	temA[0] = -1;
	temB[0] = -1;
	//0번을 일단 -1로 초기화 시킨다. (0번은 아예 알고리즘 내에 고려사항이 아니므로 그냥 단순히 초기화 시키는 용도)
	//그래서 이후 for문은 다 1로시작 의도한 크기번째에서 종료
	for (int i = 1; i < 11; i++)
	{
		int num;
		cin >> num;
		arrA[i] = num;
		temA[i] = num;
		temB[i] = num;
	}
	cout << "정렬 되기 전의 숫자 배열" << endl;
	for (int i = 1; i < 11; i++)
	{
		cout << arrA[i] << "  ";
	}
	cout << endl;
	max_HeapSort(temA,10);
	cout << "MaxHeap sort로 정렬 후의 숫자 배열(정순배열)" << endl;
	for (int i = 1; i < 11; i++)
	{
		cout << temA[i] << "  ";
	}
	cout << endl;
	
	min_HeapSort(temB,10);
	cout << "MinHeap sort로 정렬 후의 숫자 배열(역순배열)" << endl;
	for (int i = 1; i < 11; i++)
	{
		cout << temB[i] << "  ";
	}
	cout << endl;
	
	cout << "이번엔 10만개의 랜덤 수를 정렬할때의 시간 비교" << endl;
	clock_t Max_start, Max_end;
	clock_t Min_start, Min_end;
	float Max_res, Min_res;
	int arrB[100001];
	int temC[100001];
	int temD[100001];
	//10만도 동일하게 +1만큼 배열 생성
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
	cout << "MaxHeap sort 소요 시간 = " << Max_res << "ms" << endl;
	cout << "MinHeap Sort 소요 시간 = " << Min_res << "ms" << endl;
	//시간 재고
	checkSort(temC, 100000);
	//maxheap로 정렬한건 checksort로 확인
	checkSort_R(temD, 100000);
	//minheap로 정렬한건 checksort_R로 확인
}
void checkSort(int a[], int n)
//정순 정렬이므로 체크소트는 단순히 배열 크기만큼 돌리면서 i번째 수가 i+1번째 수보다 작거나 같으면 sorted는 true 크면 false
//각각에 맞는 메세지 출력
//저번이랑 달라진건 전에는 0부터 n-2까지 비교 이번에는 1번부터 배열 시작이므로 1부터 n-1까지 비교
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
	//일단 부모노드의 값을 따로 저장해두고
	int j;
	for (j = 2 * parent; j <= size; j = 2 * j)
		//*2를하면 left로 가게 된다 즉 아래로 계속 내려가면서 비교
		//j>size면 아래로 다 돌면서 정렬한거 
	{
		if (j < size && a[j] < a[j + 1])
			//j<size면 형제가 있으니 형제중 큰값 찾고
		{
			j = j + 1;
		}
		//형제중 큰값이 j가됨
		if (v >= a[j])
		//형제중 큰값이랑 부모랑 비교
		{
			break;
		//부모가 크거나 같으면 바꿀 필요가 없으니 그대로 for문 벗어나고
		}
		else
		{
			a[j / 2] = a[j]; // 부모가 작으면 a[j]를 부모 노드로 이동
		}
	}
	a[j / 2] = v;
	//부모가 크면 그대로 부모값이 다시 부모노드에 들어가고
	//부모가 작으면 j는 2배가 되어 부모의 값이 자식노드에 들어가게된다.
}
void max_HeapSort(int a[], int n)
{
	int i, temp;
	for (i =n / 2; i >= 1; i--)  // 배열 a[]를 히프로 변환
	{
		max_heapify(a, i, n); //새로 만들 heap은 배열에 들어간 원소수/2 만큼의 작은heap이 있다고 생각하면 됨
		//그리고 아래거에서부터 비교할거이므로 1부터 n/2까지
	}
	for (i = n-1 ; i >= 1; i--)
	{ // 배열 a[]를 오름차순으로 정렬
		temp = a[1]; //max heap이므로 a[1]은 제일 큰 원소
		a[1] = a[i + 1]; // a[1]과 정렬되지 않은 제일 끝의 원소 교체
		a[i + 1] = temp;//제일 끝의 원소가 제일 큰 원소로 들어감 이제 가장 마지막 원소는 정렬된 상태
		max_heapify(a, 1, i); //이걸 n번만큼 반복 
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
