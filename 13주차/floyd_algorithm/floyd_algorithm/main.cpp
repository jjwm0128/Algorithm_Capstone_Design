#include<iostream>
#define inf 999
using namespace std;
void floyd2(int n, const int W[][5], int D[][5], int P[][5]);
void path(int q, int r, int P[][5]);
void display_path(int q, int r, int P[][5]);
int main()
{
	cout << "12171856 �ֿ�� 13���� �ǽ�" << endl << endl;
	int D[5][5];
	//D�� ������ ������ �ִܰŸ�
	int P[5][5];
	//[1][2]�� 4�� 1���� 2�ΰ����� 4�� ���� ���°� ���ٴ°��� �����ϴ� �迭
	const int W[5][5] = {
		{0,1,inf,1,5},{9,0,3,2,inf},{inf,inf,0,4,inf},{inf,inf,2,0,3},{3,inf,inf,inf,0}
	};
	//W�� ����ġ�� ����� ������Ľ� ǥ��
	//0�� �ڱ��ڽ�, inf�� �ѹ��� ���� ������. inf�� 999�� �����Ͽ���
	floyd2(5, W, D, P);
	display_path(2, 5, P);
	display_path(5, 3, P);
	display_path(1, 3, P);

}
void floyd2(int n, const int W[][5],int D[][5], int P[][5]) 
//floyd2 �˰���
{
	int i, j, k;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			P[i][j] = 0;
			//�ϴ� p�� 0���� �ʱ�ȭ
			D[i][j] = W[i][j];
			//D�� W������ �ʱ�ȭ
		}

	for (k = 0; k < n; k++)
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if (D[i][k] + D[k][j] < D[i][j]) 
				//D�� ���İ��°Ͱ� �׳ɰ��°��� ���Ͽ� ���İ��°� �� �������̸�
				{
					P[i][j] = k + 1;
					//���İ� ��ġ ����
					D[i][j] = D[i][k] + D[k][j];
					//D[i][j]�� ���İ� ������ �ٽ� ����
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
		//0�� �ƴϸ� ��� ���İ���
	{
		path(q, P[q-1][r-1],P);
		//5���� ���İ��°����� �ּ��� �Ÿ��� �ϴ� ����
		printf("v%d -> ", P[q-1][r-1]);
		path(P[q-1][r-1], r,P);
		//���İ��°����� ���������� �ּ��� �Ÿ�
	}
}
void display_path(int q, int r, int P[][5])
{
	cout << "The shortest path("<<q<<", "<<r<<") is v" << q << " -> ";
	path(q, r, P);
	cout << "v" << r << endl << endl;
//���� ��δ� ����� -> �������� -> ������ �̰��� ����ϴ� �Լ�
}