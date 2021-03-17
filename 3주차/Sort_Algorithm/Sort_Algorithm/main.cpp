#include <iostream>
#include <ctime>
using namespace std;
void checkSort(int a[], int n);
void MergeSort(int size, int* arr);
void Merge(int h, int m, int* x1, int* x2, int* arr);
void SelectionSort(int size, int* arr);
int main()
{
	cout << "12171856 주우민 세번째 실습 과제" << endl;
	cout << "10개의 수가 제대로 정렬되는지 확인" << endl << "10개의 수를 입력하시오" << endl;
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
	cout << "정렬 되기 전의 숫자 배열" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << arrA[i] << "  ";
	}
	cout << endl;
	MergeSort(10, temA);
	cout << "Merge sort로 정렬 후의 숫자 배열" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << temA[i] << "  ";
	}
	cout << endl;
	SelectionSort(10, temB);
	cout << "Selection sort로 정렬 후의 숫자 배열" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << temB[i] << "  ";
	}
	cout << endl;
	cout << "이번엔 10만개의 랜덤 수를 정렬할때의 시간 비교" << endl;
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
	cout << "Merge sort 소요 시간 = " << Merge_res << "ms" << endl;
	cout << "Selection Sort 소요 시간 = " << Selection_res << "ms" << endl;
	checkSort(temC, 100000);
	checkSort(temD, 100000);
}
void checkSort(int a[], int n)
//정순 정렬이므로 체크소트는 단순히 배열 크기만큼 돌리면서 i번째 수가 i+1번째 수보다 작거나 같으면 sorted는 true 크면 false
//각각에 맞는 메세지 출력
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
//합병 정렬의 원리는 배열을 하나의 값이 남을때까지 계속 분열해서
//분열된 배열끼리 비교해서 재배열한다
{
	{
		int n = size;
		// 새롭게 배열을 만들어야 하는데 이크기는 원래 배열의 크기와 동일
		if (n > 1)
		{
			int h = n / 2;
			int m = n - h;
			//배열을 두분류로 나눠야 하니 h와 m값 이렇게 설정
			int* x1 = new int[h];
			int* x2 = new int[m];
			//h크기의 int배열 x1 생성
			//m크기의 int배열 x2 생성
			for (int i = 0; i <= h - 1; i++)
			{
				x1[i] = arr[i];
			}
			//배열 앞부분에 있는것들은 x1에 담고
			for (int i = 0; i <= m - 1; i++)
			{
				x2[i] = arr[i + h];
			}
			//배열 뒷부분에 있는것들은 x2에 담는다
			MergeSort(h, x1);
			//앞부분을 담은 것들을 또 분열시킨다
			//재귀함수이므로 n<=1이 될때 까지 분열
			MergeSort(m, x2);
			//뒷부분을 담은 것들도 마찬가지
			Merge(h, m, x1, x2, arr);
			//이제 분열된 배열들을 조건에 맞춰 다시 합친다
		}
	}
}
void Merge(int h, int m, int* x1, int* x2, int* arr)
//분열된 배열들을 합치는 알고리즘
{
	int i, j, k;
	i = 0;
	j = 0;
	k = 0;
	while (i <= h - 1 && j <= m - 1)
		//i나 j가 커지다 h-1이나 m-1이 되면 어느 한 배열은 전부 합쳐질 배열에 들어갔다는 의미
		//따라서 나머지 한 배열을 넣는걸 while문 밖에 둔다
	{
		if (x1[i] <= x2[j])
			//x1배열과 x2배열을 비교해서 작은값을 가진것부터 두개를 합칠 배열에 들어감
			//그리고 더 작은값을 가졌던 배열은 앞에 값이 새로운곳으로 들어갔으므로 ++해준다
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
		//새로운 배열에 들어갈때마다 k++
	}
	//i나 j가 커져서 h-1이나 m-1즉 어느 한 배열이 전부 합쳐질 배열에 들어가면 나머지 한 배열을 합쳐질 배열에 뒤로 넣으면 됨
	if (i > h - 1)
		//x1 배열에 있는 값들이 모두 새 배열로 들어가면
	{
		for (j; j <= m - 1; j++)
		{
			arr[k] = x2[j];
			k++;
			//x2배열에 남은 값들을 새배열의 뒤로 들어가게됨
		}
	}
	else
	{
		for (i; i <= h - 1; i++)
		{
			arr[k] = x1[i];
			k++;
		}
		//반대의 경우 마찬가지
	}
	delete[] x1;
	delete[] x2;
	//x1 x2를 모두 새배열로 넣었으므로 delete해준다
	//함수 mergesort에서 logn 만큼 merge에서 n만큼 시간복잡도이므로
	//결국 mergesort 알고리즘의 시간복잡도는 O(nlogn)
}
void SelectionSort(int size, int* arr)
//selection sort는 현재의 값이 최소값이라 가정 배열을 쭉 scan하면서 그중 최소값이랑 자리변경
{
	for (int i = 0; i < size; i++)
	{
		int nth = i;
		for (int j = i + 1; j < size; j++)
			//배열을 쭉 스캔하다가
		{
			if (arr[j] < arr[nth])
				//배열 내에서 작은값(j번째라 가정)을 발견하면 nth가 j로 바뀌어(즉 이제 j번째 값이랑 비교) 계속 스캔
			{
				nth = j;
			}
			//여기를 지나면 첫번째 값과 그 이후의 배열 내에서 최소값을 찾아낸거 
		}
		int temp = arr[nth];
		arr[nth] = arr[i];
		arr[i] = temp;
		//첫번째 값과 배열내 최소값을 서로 자리 이동
	}
	//이거를 배열 끝에있는 숫자까지 계속 진행
	//비교횟수는 (n-1) + (n-2)....+1 -> n(n-1)/2 
	//결국 selection sort 알고리즘의 시간복잡도는 O(n^2)
}