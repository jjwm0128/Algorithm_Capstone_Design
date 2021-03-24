#include <iostream>
#include <ctime>
using namespace std;
void QuickSort(int a[], int l, int r);
void swap(int a[], int b, int c);
void checkSort(int a[], int n);
int main()
{
	cout << "12171856 주우민 네번째 실습 과제" << endl;
	cout << "10개의 수가 제대로 정렬되는지 확인" << endl << "10개의 수를 입력하시오" << endl;
	int arrA[10];
	int temA[10];
	for (int i = 0; i < 10; i++)
	{
		int num;
		cin >> num;
		arrA[i] = num;
		temA[i] = num;
	}
	//10개 수 받고 그걸 배열에 넣는다. 원 배열을 해치지 않기위해 원배열 복사한것을 정렬해보려고 temA도 만들고 arrA에서 복사
	cout << "정렬 되기 전의 숫자 배열" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << arrA[i] << "  ";
	}
	cout << endl;
	//정렬되기 전 배열 출력
	QuickSort(temA,0,9);
	//퀵소트 실행
	cout << "Merge sort로 정렬 후의 숫자 배열" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << temA[i] << "  ";
	}
	//배열이 정렬 잘 됐나 확인
	cout << endl;
	cout << "10만개의 수를 quick sort할때 소요시간" << endl;
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
	//이번엔 10만개의 수가 들어간 배열 
	//srand rand함수 써서 랜덤하게 10만개의 값 넣고 위와 동일하게 배열 하나 더 만들어 저장
	Quick_start = clock();
	QuickSort(temB,0,99999);
	Quick_end = clock();
	Quick_res = (float)(Quick_end - Quick_start);
	cout << "Quick sort 소요 시간 = " << Quick_res << "ms" << endl;
	//퀵소트 실행후 소요시간 출력
	checkSort(temB, 100000);
	//10만 크기의 배열이 잘 정렬되었나 확인
}
void QuickSort(int a[], int l, int r)
//퀵소트 정의
{
	int i, j, m, v;
	if (r - l > 1) 
	//쪼개진 배열안의 개수가 3개 이상이면
	{
		m = (l + r) / 2;
		//m은 l과 r의 중간값
		if (a[l] > a[m]) swap(a, l, m);
		if (a[l] > a[r]) swap(a, l, r);
		if (a[m] > a[r]) swap(a, m, r);
		//일단 첫번째, 중간번째, 마지막 숫자를 비교해서 정렬한다.
		swap(a, m, r - 1);
		//첫번째 중간번째 마지막 숫자는 정렬되어있으므로 m번째 값을 피봇으로 정할것이므로 피봇과 마지막 -1번째 숫자를 일단 바꿔주고
		v = a[r - 1]; i = l; j = r - 1;
		//밑에서 전위 연산자를 사용할것 이므로 i는첫번째 j는 피봇이랑 동일
		for (; ; ) {
			while (a[++i] < v);
			//처음 while문에서는 두번째값부터 피봇이랑 비교
			//피봇보다 큰 수를 스캔하면 while문 빠져나옴
			while (a[--j] > v);
			//처음 while문에서는 피봇 전값이랑 비교
			//피봇보다 작은 수를 스캔하면 while문 빠져나옴
			if (i >= j) break;
			//만약에 i>=j라면 즉 i와 j가 교차하면 피봇 자리를 찾은거니까 for문 빠져나옴
			swap(a, i, j);
			//교차하지 않았으면 스캔한 두수 바꾸기
		}
		swap(a, i, r - 1);
		//피봇 자리 i를 찾았으므로 피봇자리에 피봇을 위치시키고
		QuickSort(a, l, i - 1);
		//피봇 왼쪽을 퀵소트 돌리고
		QuickSort(a, i + 1, r);
		//피봇 오른쪽을 퀵소트 돌리고
	}
	else if (a[l] > a[r]) swap(a, l, r);
	//배열안의 개수가 2개 이하면 그냥 그 두수만 비교해서 스왑
}
void swap(int a[], int b, int c)
//간단한 스왑함수
{
	int temp;
	temp = a[b];
	a[b] = a[c];
	a[c] = temp;
}
void checkSort(int a[], int n)
//정순 정렬이므로 체크소트는 단순히 배열 크기만큼 돌리면서 i번째 수가 i+1번째 수보다 작거나 같으면 sorted는 true 크면 false
//각각에 맞는 메세지 출력
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