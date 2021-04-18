#include "cuda_runtime.h"
#include "device_launch_parameters.h"
//쿠다 프로그래밍을 위한 헤더파일
#include <iostream>
#include <ctime>
using namespace std;
void QuickSort(int a[], int l, int r);
void ShellSort(int a[], int n);
void oddeven(int a[], int n);
__global__ void odd(int* x, int n);
__global__ void even(int* x, int n);
void swap(int a[], int b, int c);
void checkSort(int a[], int n);

int main()
{
	cout << "12171856 주우민 첫번째 과제" << endl << endl;

	clock_t Quick_start, Quick_end;
	float Quick_res;

	clock_t OddCuda_start, OddCuda_end;
	float OddCuda_res;

	clock_t Shell_start, Shell_end;
	float Shell_res;
	//각각 quick sort, oddeven sort, shell sort의 시간을 측정하기 위한 변수들

	int arr1[5000];
	int temA1[5000];
	int temB1[5000];
	int temC1[5000];
	//첫번째는 5천개씩

	int arr2[50000];
	int temA2[50000];
	int temB2[50000];
	int temC2[50000];
	//두번째는 5만개씩

	int arr3[500000];
	int temA3[500000];
	int temB3[500000];
	int temC3[500000];
	//세번째는 50만개씩

	int arr[10];
	for (int i = 0; i < 10; i++)
	{
		arr[i] = 1;
	}
	
	OddCuda_start = clock();
	oddeven(arr, 10);
	OddCuda_end = clock();
	OddCuda_res = (float)(OddCuda_end - OddCuda_start);
	//실험해보니 어떠한 배열을 복사한 두배열을 oddeven 함수를 각각 돌려보면 첫번째 호출할때 비정상적으로 오래걸림 
	//즉main에서 cuda이용 함수를 처음 불러올때 시간이 더 소요된다 판단
	//정확한 시간계산을 위해 단순히 oddeven 한번 불러오는용
	

	srand(time(NULL));
	for (int i = 0; i < 5000; i++)
	{
		arr1[i] = rand() % 5000;
		temA1[i] = arr1[i];
		temB1[i] = arr1[i];
		temC1[i] = arr1[i];
	}
	srand(time(NULL));
	for (int i = 0; i < 50000; i++)
	{
		arr2[i] = rand() % 50000;
		temA2[i] = arr2[i];
		temB2[i] = arr2[i];
		temC2[i] = arr2[i];
	}
	srand(time(NULL));
	for (int i = 0; i < 500000; i++)
	{
		arr3[i] = rand() % 500000;
		temA3[i] = arr3[i];
		temB3[i] = arr3[i];
		temC3[i] = arr3[i];
	}
	//정확한 시간비교를 위해 5천, 5만, 50만개 크기의 배열에 랜덤으로 원소를 채워놓고 그거를 복사한 배열을 sort

	Quick_start = clock();
	QuickSort(temA1, 0, 4999);
	Quick_end = clock();
	Quick_res = (float)(Quick_end - Quick_start);
	cout << "Quick sort 5천개 소요 시간 = " << Quick_res << "ms" << endl;

	Shell_start = clock();
	ShellSort(temB1, 5000);
	Shell_end = clock();
	Shell_res = (float)(Shell_end - Shell_start);
	cout << "Shell sort 5천개 소요 시간 = " << Shell_res << "ms" << endl;

	OddCuda_start = clock();
	oddeven(temC1, 5000);
	OddCuda_end = clock();
	OddCuda_res = (float)(OddCuda_end - OddCuda_start);
	cout << "OddCuda sort 5천개 소요 시간 = " << OddCuda_res << "ms" << endl;
	//5천개짜리 배열 sort하고 시간 출력
	
	checkSort(temA1, 5000);
	checkSort(temB1, 5000);
	checkSort(temC1, 5000);
	cout << endl;
	//sort함수를 거친 배열이 정렬 됐는지 확인

	Quick_start = clock();
	QuickSort(temA2, 0, 49999);
	Quick_end = clock();
	Quick_res = (float)(Quick_end - Quick_start);
	cout << "Quick sort 5만개 소요 시간 = " << Quick_res << "ms" << endl;

	Shell_start = clock();
	ShellSort(temB2, 50000);
	Shell_end = clock();
	Shell_res = (float)(Shell_end - Shell_start);
	cout << "Shell sort 5만개 소요 시간 = " << Shell_res << "ms" << endl;

	OddCuda_start = clock();
	oddeven(temC2, 50000);
	OddCuda_end = clock();
	OddCuda_res = (float)(OddCuda_end - OddCuda_start);
	cout << "OddCuda sort 5만개 소요 시간 = " << OddCuda_res << "ms" << endl;

	checkSort(temA2, 50000);
	checkSort(temB2, 50000);
	checkSort(temC2, 50000);
	cout << endl;

	Quick_start = clock();
	QuickSort(temA3, 0, 499999);
	Quick_end = clock();
	Quick_res = (float)(Quick_end - Quick_start);
	cout << "Quick sort 5십만개 소요 시간 = " << Quick_res << "ms" << endl;

	Shell_start = clock();
	ShellSort(temB3, 500000);
	Shell_end = clock();
	Shell_res = (float)(Shell_end - Shell_start);
	cout << "Shell sort 5십만개 소요 시간 = " << Shell_res << "ms" << endl;
	
	OddCuda_start = clock();
	oddeven(temC3, 500000);
	OddCuda_end = clock();
	OddCuda_res = (float)(OddCuda_end - OddCuda_start);
	cout << "OddCuda sort 5십만개 소요 시간 = " << OddCuda_res << "ms" << endl;
	
	
	checkSort(temA3, 500000);
	checkSort(temB3, 500000);
	checkSort(temC3, 500000);
	//5만, 5십만 크기의 배열들도 동일하게 진행
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
			//while문의 첫번째 루프에서는 두번째값부터 피봇이랑 비교
			//피봇보다 큰 수를 스캔하면 while문 빠져나옴
			while (a[--j] > v);
			//while문의 첫번째 루프에서는 피봇 전값이랑 비교
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
void ShellSort(int a[], int n)
//쉘소트는 삽입정렬과 유사하다
//삽입정렬은 역순으로 정렬되어있을때 최악의 시간복잡도
//이를 보완하기 위해 간격을 두어 어느정도 정렬을 하고
//마지막에 gap을 1로두어 정렬을하면 어느정도 정렬이 된 배열을 정렬하는 삽입정렬이라 생각 가능
//따라서 삽입정렬보다 빠른 시간복잡도를 가짐
//여기서 사용한 방식은 A003462 방식으로 worst일떼 n^(3/2)시간복잡도를 가짐
{
	int k = 1, gap = 1;
	for (;;)
	{
		gap = pow(3, k);
		gap = (gap - 1) / 2;
		k++;
		if (gap > n / 3) break;
	}
	//A003462 방식으로 gap을 구한다
	for (; gap > 0; gap = gap / 3)
	//가장 큰 gap에서부터 시작해서 gap이 1이될때까지 for문은 돌아간다
	{
		for (int i = gap; i < n; i++)
		//gap만큼 떨어진 값들을 삽입정렬 하는 알고리즘
		//예를들어 n이 10이고 gap이 3이 되었다 치자
		//i가 3, 226번째 줄에서 3번 보관하고 for문에서 0번이랑 비교하고 둘이 정렬
		//i++ 쭉 되다 i가 6이 되면 226번째줄에서 6번 보관하고  3번이랑 비교, 3번이 더 크면 정렬하고 또 3번이랑 0번 비교하는 알고리즘
		//이렇게 0369 147 258 정렬됨
		{
			int j = 0;
			int temp = a[i];
			for (j = i; j >= gap && a[j - gap] > temp; j = j - gap)
			{
				a[j] = a[j - gap];
			}
			a[j] = temp;
		}
	}
}
void oddeven(int a[], int n)
//oddeven sort하는 함수
{
	int* d;
	//device에서 사용할 배열
	cudaMalloc((void**)&d, n * sizeof(int));
	//device에 배열 크기만큼 메모리 할당
	cudaMemcpy(d, a, n * sizeof(int), cudaMemcpyHostToDevice);
	//gpu meemory에 배열 a를 d로 복사
	for (int i = 0; i <= n/2 ; i++)
	{
		even << <n/2, 1 >> > (d, n); //짝수
		//01 23 45 이런식으로 비교해서 정렬
		//비교하는 과정은 cuda를 이용 동시에 진행됨
		//<<<n/2,1>>> 의미는 동시에 n/2번의 함수가 호출된다는 뜻
		odd << <n/2, 1 >> > (d, n);  //홀수
		//위와 동일하게 12 34 56 이런식으로 비교해서 정렬

		//위 과정을 2/n번만큼 실행하면 끝
	}
	cudaMemcpy(a, d, n * sizeof(int), cudaMemcpyDeviceToHost);
	//결과를 cpu memory에 a로 복사
	cudaFree(d);
	//해제
}
__global__ void odd(int* x, int n)
//쿠다 프로그래밍으로 구현한 odd even
//host: cpu, device: gpu
//cpu를 gpu로 옮기고 gpu가 처리한걸 다시 cpu로 복사하는 시스템
//__global__의 의미는 device에서 실행 host에서 호출
{
	int id = blockIdx.x;
	//블록 넘버를 id에 담고
	if (id * 2 + 2 < n)
	//n이 100이라 가정하면 12 34 56 78 비교하다 97 98 에서 끝나야됨
	{
		if (x[id * 2 +1] > x[id * 2 + 2])
		//12 34 56 ... 비교하고 정렬
		{
			int temp = x[id * 2 + 1];
			x[id * 2 +1] = x[id * 2 + 2];
			x[id * 2 + 2] = temp;
		}
	}
}
__global__ void even(int* x, int n)
//odd 함수와 동일한데 01 23 45... 이런식으로 비교
{
	int id = blockIdx.x;
	if (id * 2 + 1 < n)
	//n이 100이라 가정하면 01 23 45 비교하다 98 99 에서 끝나야됨
	{
		if (x[id * 2] > x[id * 2 + 1])
		{
			int temp = x[id * 2];
			x[id * 2] = x[id * 2 + 1];
			x[id * 2 + 1] = temp;
		}
	}
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
