#include<iostream>
#include<string>
using namespace std;
int leven_a(wstring source, wstring target);
double leven_b(wstring source, wstring target);
int min(int a, int b, int c);
double min(double a, double b, double c);

int main()
{
	cout << "12171856 �ֿ�� �ι�° ����" << endl << endl;
	wstring source1 = L"gumbo"; wstring source2 = L"Levenshtein"; wstring source3 = L"TACTG"; wstring source4 = L"����Ÿ���̴�";
	wstring target1 = L"gambol"; wstring target2 = L"Meilenstein"; wstring target3 = L"CATGACTG"; wstring target4 = L"�����ͺ��̽�����";
	//�ѱ� ������ ���� wstring���� ����

	cout << "��ȯ, ����, ���� ����� ��� 1�̰� source=GUMBO tagrget=GAMBOL" << endl;
	leven_a(source1, target1);
	cout << "��ȯ, ����, ���� ����� ���� 0.3, 0.7, 0.5�̰� source=GUMBO tagrget=GAMBOL" << endl;
	leven_b(source1, target1);

	cout << "��ȯ, ����, ���� ����� ���� 0.3, 0.7, 0.5�̰� source=Levenshtein tagrget=Meilenstein" << endl;
	leven_b(source2, target2);
	cout << "��ȯ, ����, ���� ����� ���� 0.3, 0.7, 0.5�̰� source=TACTG tagrget=CATGACTG" << endl;
	leven_b(source3, target3);
	cout << "��ȯ, ����, ���� ����� ���� 0.3, 0.7, 0.5�̰� source=����Ÿ���̴� tagrget=�����ͺ��̽�����" << endl;
	leven_b(source4, target4);

}

int leven_a(wstring source, wstring target)
//���� ���� ��ü ����� ��� 1�� �˰���
{
	int row, col, result;
	int insert_cost = 0;
	int delte_cost = 0;
	int change_cost = 0;

	row = target.size() + 1;
	col = source.size() + 1;


	int** leven_distance = new int* [row];
	int** path = new int* [row];
	//�Ÿ��� ������ leven distace, ��� �Դ����� ������ path �迭 ����
	//path�迭�� ��� 0���� �밢���������� 0 ����, ��ü������� �밢���������� 1 ����, ���� ������� ������ ������ 2����, ���� ������� ���ʿ��� ������ 3���� 

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
	//�� 0���� �ʱ�ȭ

	for (int i = 1; i < row; i++)
	{
		leven_distance[i][0] = i * 1;
		path[i][0] = 2;
		//��� �����̹Ƿ� path�� 2 ����
	}
	for (int j = 1; j < col; j++)
	{
		leven_distance[0][j] = j * 1;
		path[0][j] = 3;
		//��� �����̹Ƿ� path�� 3����
	}
	//[0][0] ĭ�� �����̹Ƿ� ����� ���ϸ� source���� j��ŭ ����, target���� i��ŭ �����ؾ� �ϰ� �Ѵ� ����� 1�̹Ƿ� �̷��� ������ش�
	int up = 0, left = 0, diagonal = 0;
	for (int i = 1; i < row; i++)
	{
		for (int j = 1; j < col; j++)
		{
			if (target[i - 1] == source[j - 1])
				//ù���ں��� �� ���ϴµ� ���ϴ� ���ڰ� ������ ���� �밢�� �����ִ� �� �״��
			{
				leven_distance[i][j] = leven_distance[i - 1][j - 1];
				path[i][j] = 0;
				//�׸��� path�迭�� 0 ����
			}
			else
				//�ٸ��� ������ +1(����), ���ʰ� +1(����), ���� �밢���� +1(��ü)�� ���� �������� [i][j]�� ���̵ȴ�
			{
				up = leven_distance[i - 1][j];
				left = leven_distance[i][j - 1];
				diagonal = leven_distance[i - 1][j - 1];

				leven_distance[i][j] = min(up + 1, left + 1, diagonal + 1);
				if (min(up, left, diagonal) == up)
				{
					path[i][j] = 2;
					//������ �Ͼ���� path�� 2����
				}
				else if (min(up, left, diagonal) == left)
				{
					path[i][j] = 3;
					//������ �Ͼ���� path�� 3����
				}
				else
				{
					path[i][j] = 1;
					//��ȯ�� �Ͼ���� path�� 1����
				}
			}
		}
	}

	cout << "------------------leven_distance �迭------------------" << endl;
	for (int i = 0; i < row; i++)
		//���� �˰������� ������� leven_distance �迭
	{
		for (int j = 0; j < col; j++) {

			cout << leven_distance[i][j] << " ";

		}
		cout << endl;
	}

	cout << "------------------leven_distance �迭 ------------------" << endl;
	result = leven_distance[row - 1][col - 1];
	//�迭�� �޸𸮿��� �����ϱ� ���� ����� ����

	int i = row - 1, j = col - 1;
	int count = 0;
	//[0]][0]���� ����� ������ �������� �󸶳� �ɷ��� ������ ����
	int tempsize = row * col;
	//����������� [0][0]���� ��� �����ĸ� �迭�� ����� �����Ұǵ� ũ�⸦ ��Ȯ�� ���� ���� row * col ũ���
	int* path_num_reverse = new int[tempsize];
	//����������� [0][0]���� ��� �����ĸ� ������ �迭 �� ����������� ���� ����

	while (i != 0 || j != 0)
		//����������� [0][0]�� �Ǳ� ������ �� ����
	{
		if (path[i][j] == 0)
			//����x�� �밢������ �Դ�
		{
			i--;
			j--;
			//�밢�� ���� ���� ����
			path_num_reverse[count] = 0;
			//�밢�� ���� ���ٰ� ����
			count++;
		}
		else if (path[i][j] == 1)
			//��ȯ�����̴� �밢������ �Դ�
		{
			i--;
			j--;
			//�밢�� ���� ���� ����
			path_num_reverse[count] = 1;
			//�밢�� ���� ���ٰ� ����
			count++;
			change_cost += 1;
			//��ȯ ������ ������ ��ȯ ������ +
		}
		else if (path[i][j] == 2)
			//�����̴� ������ �Դ�
		{
			i--;
			//���� ����
			path_num_reverse[count] = 2;
			//���� ���ٰ� ����
			count++;
			insert_cost += 1;
			//���� ������ ������ ���� ������ +
		}
		else if (path[i][j] == 3)
			//���� �����̴� ���ʿ��� �Դ�
		{
			j--;
			//�������� ����
			path_num_reverse[count] = 3;
			//�������� ���ٰ� ����
			count++;
			delte_cost += 1;
			//���� ������ ������ ���� ������ +
		}
	}
	//�̷��� while���� ���������� [0][0]���� ���� �Ϸ�

	cout << endl;
	cout << "�������" << endl;

	for (int i = 1;i <= count; i++)
	//���� ������ ����Ȱ� ������ �����ϸ� [0][0]���� ��������� � �������� �� �� �����Ƿ� ���
	{
		if (path_num_reverse[count - i] == 0)
		{
			cout << "����x  ";
		}
		else if (path_num_reverse[count - i] == 1)

		{
			cout << "��ȯ  ";
		}
		else if (path_num_reverse[count - i] == 2)
		{
			cout << "����  ";
		}
		else if (path_num_reverse[count - i] == 3)
		{
			cout << "����  ";
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
	//�����Ҵ��� �迭�� delete

	cout << "��ȯ����: " << change_cost << " ���Կ���: " << insert_cost << " ��������: " << delte_cost
		<< " Levenshtein Distance = " << result << endl << endl << endl;
	//��� ���
	return result;
}

double leven_b(wstring source, wstring target)
//���Ժ�� 0.7, ������� 0.5, ��ȯ��� 0.3�� �˰���
//double �迭�� ������ְ� ��븸 �޶����� �������� �Ȱ����Ƿ� �ּ� ����
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
	//[0][0] ĭ�� �����̹Ƿ� ����� ���ϸ� source���� j��ŭ ����, target���� i��ŭ �����ؾ� �ϰ� ���� ����� 0.5, 0.7�̹Ƿ� �̷��� ������ش�
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

	cout << "------------------leven_distance �迭------------------" << endl;
	for (int i = 0; i < row; i++)
	{

		for (int j = 0; j < col; j++) {

			cout << leven_distance[i][j] << "  ";

		}
		cout << endl;
	}

	cout << "------------------leven_distance �迭 ------------------" << endl;
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
	cout << "�������" << endl;
	for (int i = 1; i <= count; i++)
	{
		if (path_num_reverse[count - i] == 0)
		{
			cout << "����x  ";
		}
		else if (path_num_reverse[count - i] == 1)

		{
			cout << "��ȯ  ";
		}
		else if (path_num_reverse[count - i] == 2)
		{
			cout << "����  ";
		}
		else if (path_num_reverse[count - i] == 3)
		{
			cout << "����  ";
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

	cout << "��ȯ����: " << change_cost << " ���Կ���: " << insert_cost << " ��������: " << delte_cost
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