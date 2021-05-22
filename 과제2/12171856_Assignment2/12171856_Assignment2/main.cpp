#include<iostream>
#include<string>
using namespace std;
int leven_a(wstring source, wstring target);
double leven_b(wstring source, wstring target);
int min(int a, int b, int c);
double min(double a, double b, double c);

int main()
{
	cout << "12171856 주우민 두번째 과제" << endl << endl;
	wstring source1 = L"gumbo"; wstring source2 = L"Levenshtein"; wstring source3 = L"TACTG"; wstring source4 = L"데이타마이닝";
	wstring target1 = L"gambol"; wstring target2 = L"Meilenstein"; wstring target3 = L"CATGACTG"; wstring target4 = L"데이터베이스설계";
	//한글 지원을 위해 wstring으로 선언

	cout << "교환, 삽입, 삭제 비용이 모두 1이고 source=GUMBO tagrget=GAMBOL" << endl;
	leven_a(source1, target1);
	cout << "교환, 삽입, 삭제 비용이 각각 0.3, 0.7, 0.5이고 source=GUMBO tagrget=GAMBOL" << endl;
	leven_b(source1, target1);

	cout << "교환, 삽입, 삭제 비용이 각각 0.3, 0.7, 0.5이고 source=Levenshtein tagrget=Meilenstein" << endl;
	leven_b(source2, target2);
	cout << "교환, 삽입, 삭제 비용이 각각 0.3, 0.7, 0.5이고 source=TACTG tagrget=CATGACTG" << endl;
	leven_b(source3, target3);
	cout << "교환, 삽입, 삭제 비용이 각각 0.3, 0.7, 0.5이고 source=데이타마이닝 tagrget=데이터베이스설계" << endl;
	leven_b(source4, target4);

}

int leven_a(wstring source, wstring target)
//삭제 삽입 교체 비용이 모두 1인 알고리즘
{
	int row, col, result;
	int insert_cost = 0;
	int delte_cost = 0;
	int change_cost = 0;

	row = target.size() + 1;
	col = source.size() + 1;


	int** leven_distance = new int* [row];
	int** path = new int* [row];
	//거리를 저장할 leven distace, 어디서 왔는지를 저장할 path 배열 생성
	//path배열은 비용 0으로 대각선에서오면 0 저장, 교체비용으로 대각선에서오면 1 저장, 삽입 비용으로 위에서 왔으면 2저장, 삭제 비용으로 왼쪽에서 왔으면 3저장 

	for (int i = 0; i < row; i++)
	{
		leven_distance[i] = new int[col];
		path[i] = new int[col];
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			leven_distance[i][j] = 0;
			path[i][j] = 0;
		}
	}
	//값 0으로 초기화

	for (int i = 1; i < row; i++)
	{
		leven_distance[i][0] = i * 1;
		path[i][0] = 2;
		//모두 삽입이므로 path에 2 저장
	}
	for (int j = 1; j < col; j++)
	{
		leven_distance[0][j] = j * 1;
		path[0][j] = 3;
		//모두 삭제이므로 path에 3저장
	}
	//[0][0] 칸은 공백이므로 공백과 비교하면 source쪽은 j만큼 삭제, target쪽은 i만큼 삽입해야 하고 둘다 비용은 1이므로 이렇게 만들어준다
	int up = 0, left = 0, diagonal = 0;
	for (int i = 1; i < row; i++)
	{
		for (int j = 1; j < col; j++)
		{
			if (target[i - 1] == source[j - 1])
				//첫글자부터 쭉 비교하는데 비교하는 문자가 같으면 왼쪽 대각선 위에있는 수 그대로
			{
				leven_distance[i][j] = leven_distance[i - 1][j - 1];
				path[i][j] = 0;
				//그리고 path배열에 0 저장
			}
			else
				//다르면 위에거 +1(삽입), 왼쪽거 +1(삭제), 왼쪽 대각선위 +1(교체)중 가장 작은값이 [i][j]의 값이된다
			{
				up = leven_distance[i - 1][j];
				left = leven_distance[i][j - 1];
				diagonal = leven_distance[i - 1][j - 1];

				leven_distance[i][j] = min(up + 1, left + 1, diagonal + 1);
				if (min(up, left, diagonal) == up)
				{
					path[i][j] = 2;
					//삽입이 일어났으면 path에 2저장
				}
				else if (min(up, left, diagonal) == left)
				{
					path[i][j] = 3;
					//삭제가 일어났으면 path에 3저장
				}
				else
				{
					path[i][j] = 1;
					//교환이 일어났으면 path에 1저장
				}
			}
		}
	}

	cout << "------------------leven_distance 배열------------------" << endl;
	for (int i = 0; i < row; i++)
		//위의 알고리즘으로 만들어진 leven_distance 배열
	{
		for (int j = 0; j < col; j++) {

			cout << leven_distance[i][j] << " ";

		}
		cout << endl;
	}

	cout << "------------------leven_distance 배열 ------------------" << endl;
	result = leven_distance[row - 1][col - 1];
	//배열을 메모리에서 해제하기 전에 결과값 저장

	int i = row - 1, j = col - 1;
	int count = 0;
	//[0]][0]에서 결과가 나오는 지점까지 얼마나 걸려서 가나를 저장
	int tempsize = row * col;
	//결과지점에서 [0][0]까지 어떻게 가느냐를 배열에 만들어 저장할건데 크기를 정확히 몰라 대충 row * col 크기로
	int* path_num_reverse = new int[tempsize];
	//결과지점에서 [0][0]까지 어떻게 가느냐를 저장할 배열 즉 출발지점에서 보면 역순

	while (i != 0 || j != 0)
		//결과지점에서 [0][0]이 되기 전까지 쭉 추적
	{
		if (path[i][j] == 0)
			//연산x니 대각선에서 왔다
		{
			i--;
			j--;
			//대각선 왼쪽 위로 추적
			path_num_reverse[count] = 0;
			//대각선 위로 갔다고 저장
			count++;
		}
		else if (path[i][j] == 1)
			//교환연산이니 대각선에서 왔다
		{
			i--;
			j--;
			//대각선 왼쪽 위로 추적
			path_num_reverse[count] = 1;
			//대각선 위로 갔다고 저장
			count++;
			change_cost += 1;
			//교환 연산을 했으니 교환 연산비용 +
		}
		else if (path[i][j] == 2)
			//삽입이니 위에서 왔다
		{
			i--;
			//위로 추적
			path_num_reverse[count] = 2;
			//위로 갔다고 저장
			count++;
			insert_cost += 1;
			//삽입 연산을 했으니 삽입 연산비용 +
		}
		else if (path[i][j] == 3)
			//삭제 연산이니 왼쪽에서 왔다
		{
			j--;
			//왼쪽으로 추적
			path_num_reverse[count] = 3;
			//왼쪽으로 갔다고 저장
			count++;
			delte_cost += 1;
			//삭제 연산을 했으니 삭제 연산비용 +
		}
	}
	//이렇게 while문을 빠져나오면 [0][0]까지 추적 완료

	cout << endl;
	cout << "연산순서" << endl;

	for (int i = 1;i <= count; i++)
	//이제 역으로 저장된걸 역으로 추적하면 [0][0]에서 결과값까지 어떤 순서인지 볼 수 있으므로 출력
	{
		if (path_num_reverse[count - i] == 0)
		{
			cout << "연산x  ";
		}
		else if (path_num_reverse[count - i] == 1)

		{
			cout << "교환  ";
		}
		else if (path_num_reverse[count - i] == 2)
		{
			cout << "삽입  ";
		}
		else if (path_num_reverse[count - i] == 3)
		{
			cout << "삭제  ";
		}
	}
	cout << endl;

	for (int i = 0; i < row; i++)
	{
		delete[] leven_distance[i];
		delete[] path[i];
	}
	delete[] leven_distance;
	delete[] path;
	delete[] path_num_reverse;
	//동적할당한 배열들 delete

	cout << "교환연산: " << change_cost << " 삽입연산: " << insert_cost << " 삭제연산: " << delte_cost
		<< " Levenshtein Distance = " << result << endl << endl << endl;
	//결과 출력
	return result;
}

double leven_b(wstring source, wstring target)
//삽입비용 0.7, 삭제비용 0.5, 교환비용 0.3인 알고리즘
//double 배열로 만들어주고 비용만 달라졌고 나머지는 똑같으므로 주석 생략
{
	int row, col;
	double result;
	double insert_cost = 0;
	double delte_cost = 0;
	double change_cost = 0;

	row = target.size() + 1;
	col = source.size() + 1;

	double** leven_distance = new double* [row];
	int** path = new int* [row];

	for (int i = 0; i < row; i++)
	{
		leven_distance[i] = new double[col];
		path[i] = new int[col];
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			leven_distance[i][j] = 0;
			path[i][j] = 0;
		}
	}

	for (int i = 1; i < row; i++)
	{
		leven_distance[i][0] = i * 0.7;
		path[i][0] = 2;
	}
	for (int j = 1; j < col; j++)
	{
		leven_distance[0][j] = j * 0.5;
		path[0][j] = 3;
	}
	//[0][0] 칸은 공백이므로 공백과 비교하면 source쪽은 j만큼 삭제, target쪽은 i만큼 삽입해야 하고 각각 비용은 0.5, 0.7이므로 이렇게 만들어준다
	double up = 0, left = 0, diagonal = 0;
	for (int i = 1; i < row; i++)
	{
		for (int j = 1; j < col; j++)
		{
			if (target[i - 1] == source[j - 1])
			{
				leven_distance[i][j] = leven_distance[i - 1][j - 1];
				path[i][j] = 0;
			}
			else
			{
				up = leven_distance[i - 1][j];
				left = leven_distance[i][j - 1];
				diagonal = leven_distance[i - 1][j - 1];

				leven_distance[i][j] = min(up + 0.7, left + 0.5, diagonal + 0.3);

				if (min(up, left, diagonal) == up)
				{
					path[i][j] = 2;
				}
				else if (min(up, left, diagonal) == left)
				{
					path[i][j] = 3;
				}
				else
				{
					path[i][j] = 1;
				}
			}
		}
	}

	cout << "------------------leven_distance 배열------------------" << endl;
	for (int i = 0; i < row; i++)
	{

		for (int j = 0; j < col; j++) {

			cout << leven_distance[i][j] << "  ";

		}
		cout << endl;
	}

	cout << "------------------leven_distance 배열 ------------------" << endl;
	result = leven_distance[row - 1][col - 1];

	int i = row - 1, j = col - 1;
	int count = 0;
	int tempsize = row * col;
	int* path_num_reverse = new int[tempsize];


	while (i != 0 || j != 0)
	{
		if (path[i][j] == 0)
		{
			i--;
			j--;
			path_num_reverse[count] = 0;
			count++;
		}
		else if (path[i][j] == 1)
		{
			i--;
			j--;
			path_num_reverse[count] = 1;
			count++;
			change_cost += 0.3;
		}
		else if (path[i][j] == 2)
		{
			i--;
			path_num_reverse[count] = 2;
			count++;
			insert_cost += 0.7;
		}
		else if (path[i][j] == 3)
		{
			j--;
			path_num_reverse[count] = 3;
			count++;
			delte_cost += 0.5;
		}
	}
	cout << endl;
	cout << "연산순서" << endl;
	for (int i = 1; i <= count; i++)
	{
		if (path_num_reverse[count - i] == 0)
		{
			cout << "연산x  ";
		}
		else if (path_num_reverse[count - i] == 1)

		{
			cout << "교환  ";
		}
		else if (path_num_reverse[count - i] == 2)
		{
			cout << "삽입  ";
		}
		else if (path_num_reverse[count - i] == 3)
		{
			cout << "삭제  ";
		}
	}
	cout << endl;

	for (int i = 0; i < row; i++)
	{
		delete[] leven_distance[i];
		delete[] path[i];
	}
	delete[] leven_distance;
	delete[] path;
	delete[] path_num_reverse;

	cout << "교환연산: " << change_cost << " 삽입연산: " << insert_cost << " 삭제연산: " << delte_cost
		<< " Levenshtein Distance = " << result << endl << endl << endl;

	return result;
}



int min(int a, int b, int c)
{
	if (a <= b)
	{
		if (a <= c)
			return a;
		else
			return c;
	}
	else
	{
		if (b <= c)
			return b;
		else
			return c;
	}
}
double min(double a, double b, double c)
{
	if (a <= b)
	{
		if (a <= c)
			return a;
		else
			return c;
	}
	else
	{
		if (b <= c)
			return b;
		else
			return c;
	}
}