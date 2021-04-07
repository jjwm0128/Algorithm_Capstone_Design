#include <iostream>
using std::cout; using std::cin;  using std::endl;
void Radix_Sort(int* data, int size, int p, int k);
int main()
{
	cout << "12171856 주우민 여섯번째 실습 과제" << endl;
	cout << "8개의 수가 제대로 정렬되는지 확인" << endl << "8개의 수를 입력하시오" << endl;
	int* arrA = new int[8];
	int* temA = new int[8];
	for (int i = 0; i < 8; i++)
	{
		int num;
		cin >> num;
		arrA[i] = num;
		temA[i] = num;
	}
	//8개 수 받고 그걸 배열에 넣는다. 원 배열을 해치지 않기위해 원배열 복사한것을 정렬해보려고 temA도 만들고 arrA에서 복사
	cout << "정렬 되기 전의 숫자 배열" << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << arrA[i] << "  ";
	}
	cout << endl;
	//정렬되기 전 배열 출력
	Radix_Sort(temA, 8, 100, 10);
	//Radix 소트 실행
	cout << "Radix sort로 정렬 후의 숫자 배열" << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << temA[i] << "  ";
	}
	//배열이 정렬 잘 됐나 확인
	cout << endl;
	delete[] arrA;
	delete[] temA;
}
/**
  * @data  정수 배열
  * @size  data의 정수들의 개수
  * @p  숫자의 최대 자리수
  * @k  기수(10진법을 사용한다면 10)

  */
void Radix_Sort(int* data, int size, int p, int k) 
{
	int* counts; // 특정 자리에서 숫자들의 카운트
	int* temp; // 정렬된 배열을 담을 임시 장소
	int index, pval, i, j, n;
	// 메모리 할당
	if ((counts = new int[k]) == NULL)
		return;
	if ((temp = new int[size]) == NULL)
		return;
	for (n = 0; n < p; n++) 
	{ // 1의 자리, 10의자리, 100의 자리 순으로 진행
		for (i = 0; i < k; i++)
		{
			counts[i] = 0; // 초기화
		   // 위치값 계산.
		  // n:0 => 1,  1 => 10, 2 => 100
		}
		pval = (int)pow((double)k, (double)n);
		// 각 숫자의 발생횟수를 센다.
		for (j = 0; j < size; j++) 
		{
			// 253이라는 숫자라면
			// n:0 => 3,  1 => 5, 2 => 2
			index = (int)(data[j] / pval) % k;
			counts[index] = counts[index] + 1;
		}
		// 카운트 누적합을 구한다. 계수정렬을 위해서.
		for (i = 1; i < k; i++) 
		{
			counts[i] = counts[i] + counts[i - 1];
		}
		// 카운트를 사용해 각 항목의 위치를 결정한다.
		// 계수정렬 방식
		for (j = size - 1; j >= 0; j--) 
		{ // 뒤에서부터 시작
			index = (int)(data[j] / pval) % k;
			temp[counts[index] - 1] = data[j];
			counts[index] = counts[index] - 1; // 해당 숫자 카운트를 1 감소
		}
		// 임시 데이터 복사
		memcpy(data, temp, size * sizeof(int));
	}
	delete[] counts;
	delete[] temp;
}