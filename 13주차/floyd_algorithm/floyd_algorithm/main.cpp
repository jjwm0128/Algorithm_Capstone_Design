#include<iostream>
#define inf 999
using namespace std;
void floyd2(int n, const int W[][5], int D[][5], int P[][5]);
void path(int q, int r, int P[][5]);
void display_path(int q, int r, int P[][5]);
int main()
{
	cout << "12171856 주우민 13주차 실습" << endl << endl;
	int D[5][5];
	//D는 정점들 사이의 최단거리
	int P[5][5];
	//[1][2]가 4면 1에서 2로갈때는 4를 거쳐 가는게 좋다는것을 저장하는 배열
	const int W[5][5] = {
		{0,1,inf,1,5},{9,0,3,2,inf},{inf,inf,0,4,inf},{inf,inf,2,0,3},{3,inf,inf,inf,0}
	};
	//W는 가중치를 고려한 인접행렬식 표현
	//0은 자기자신, inf는 한번에 갈수 없을때. inf는 999로 설정하였다
	floyd2(5, W, D, P);
	display_path(2, 5, P);
	display_path(5, 3, P);
	display_path(1, 3, P);

}
void floyd2(int n, const int W[][5],int D[][5], int P[][5]) 
//floyd2 알고리즘
{
	int i, j, k;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			P[i][j] = 0;
			//일단 p는 0으로 초기화
			D[i][j] = W[i][j];
			//D는 W값으로 초기화
		}

	for (k = 0; k < n; k++)
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if (D[i][k] + D[k][j] < D[i][j]) 
				//D를 거쳐가는것과 그냥가는것을 비교하여 거쳐가는게 더 적은값이면
				{
					P[i][j] = k + 1;
					//거쳐간 위치 저장
					D[i][j] = D[i][k] + D[k][j];
					//D[i][j]를 거쳐간 값으로 다시 저장
				}

	cout << "W[i][j] is" << endl;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			cout << W[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "D[i][j] is" << endl;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			cout << D[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "P[i][j] is" << endl;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			cout << P[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;
}
void path(int q, int r,int P[][5]) 
{
	if (P[q-1][r-1] != 0) 
		//0이 아니면 어디를 거쳐간다
	{
		path(q, P[q-1][r-1],P);
		//5에서 거쳐가는곳까지 최소한 거리를 일단 가고
		printf("v%d -> ", P[q-1][r-1]);
		path(P[q-1][r-1], r,P);
		//거쳐가는곳에서 도착지까지 최소한 거리
	}
}
void display_path(int q, int r, int P[][5])
{
	cout << "The shortest path("<<q<<", "<<r<<") is v" << q << " -> ";
	path(q, r, P);
	cout << "v" << r << endl << endl;
//최종 경로는 출발지 -> 경유지들 -> 도착지 이것을 출력하는 함수
}