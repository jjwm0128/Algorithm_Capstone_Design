#include <iostream>
using std::cout; using std::endl;

int cheese_result(int cheese[][9]);			//ġ�� �ִ밪 �����ϴ� �Լ�
int cheeseWithTrap_result(int cheese[][9]); //�㵣�� �ִ����ǿ��� ġ�� �ִ밪 �����ϴ� �Լ�
int max(int a, int b);						//���� ū���� �����ϴ� �Լ�

int main()
{
	int cheese[9][9] =
	{
		{0, 0, 1, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 1, 0, 0, 0, 0},
		{0, 1, 0, 1, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 1, 0, 0, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
	int cheeseWtihTrap[9][9] =
	{
		{0, 0, 1, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 0, 2, 0},
		{1, 0, 2, 0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 1, 2, 0, 0, 0},
		{0, 1, 0, 1, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 2, 1, 2, 0},
		{0, 1, 0, 0, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0} 
	};

	cout << cheese_result(cheese) << endl;					//���� 1 ����
	cout << cheeseWithTrap_result(cheeseWtihTrap) << endl;  //���� 2 ����
}
int cheese_result(int cheese[][9])
{
	int result[9][9] = { 0, };
	//[i][j]���� �ִ� ġ� �����ϴ� �迭 �ϴ� ��簪 0 �ʱ�ȭ

	if (cheese[8][0])
		result[8][0] = 1;
	//������ġ�� �ʱ�ȭ ������ġ�� ġ� ������ 1

	for (int i = 7; i >= 0; i--)
	{
		if (cheese[i][0] == 0)
			result[i][0] = result[i + 1][0];

		else if(cheese[i][0] == 1)
			result[i][0] = result[i + 1][0] + 1;
	}
	//�� ���� ������ ��� �ؿ��� + ([i][0]�� ġ� ������ +0 ������ +1)

	for (int j = 1; j < 9; j++)
	{
		if (cheese[8][j] == 1)
			result[8][j] = result[8][j - 1] + 1;

		else
			result[8][j] = result[8][j - 1];
	}
	//�� �ؿ� ������ ��� ���ʲ� + ([8][j]�� ġ� ������ +0 ������ +1)
	//��ȭ�� ���� �ȵǴ� ���ܵ� ó�� ��

	for (int i = 7; i >= 0; i--)
	{
		for (int j = 1; j < 9; j++)
		{
			//[i][j]������ ġ�� �ִ밪�� ���ʲ� �Ʒ��� ���ؼ� ū�� + ([i][j]�� ġ� ������ +0 ������ +1)
			if (cheese[i][j] == 0)
				result[i][j] = max(result[i][j - 1], result[i + 1][j]);
			else if (cheese[i][j] == 1)
				result[i][j] = max(result[i][j - 1], result[i + 1][j]) + 1;
		}
	}

	/*
	ġ�� �ִ밪 ǥ�� ���
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << result[i][j] << " ";
		}
		cout << endl;
	}
	*/

	return result[0][8];
	//�������� ġ�� �ִ밪 ��ȯ
}

int cheeseWithTrap_result(int cheese[][9])
//�㵣�� �߰��� �㵣������ -1�� �ٲ��ִ� ����
{
	int result[9][9] = { 0, };

	if (cheese[8][0])
		result[8][0] = 1;

	for (int i = 7; i >= 0; i--)
	{
		if (cheese[i][0] == 0)
		result[i][0] = result[i + 1][0];

		else if (cheese[i][0] == 1)
			result[i][0] = result[i + 1][0] + 1;

		else if (cheese[i][0] == 2)
		{
			result[i][0] = -1;
			for (i -= 1; i >= 0; i--)
				result[i][0] = 0;
			//�� ���� ������ �߰��� �㵣�� ������ �㵣 �ִµ��� -1 �㵣 ���Ĵ� ������� �����Ƿ� 0ǥ��
		}
	}

	for (int j = 1; j < 9; j++)
	{
		if (cheese[8][j] == 0)
			result[8][j] = result[8][j - 1];

		else if (cheese[8][j] == 1)
			result[8][j] = result[8][j - 1] + 1;

		else if (cheese[8][j] == 2)
		{
			result[8][j] = -1;
			for (j += 1; j < 9; j++)
				result[8][j] = 0;
			//�� �ؿ� ������ �߰��� �㵣�� ������ �㵣 �ִµ��� -1 �㵣 ���Ĵ� ������� �����Ƿ� 0ǥ��
		}
	}

	
	for (int i = 7; i >= 0; i--)
	{
		for (int j = 1; j < 9; j++)
		{
			//[i][j]������ ġ�� �ִ밪�� ���ʲ� �Ʒ��� ���ؼ� ū�� + ([i][j]�� ġ� ������ +0 ������ +1)
			//[i][j]�� �㵣�� ������ -1ó���ؼ� �������� ����
			if (cheese[i][j] == 0)
				result[i][j] = max(result[i][j - 1], result[i + 1][j]);

			else if (cheese[i][j] == 1)
				result[i][j] = max(result[i][j - 1], result[i + 1][j]) + 1;

			else if (cheese[i][j] == 2)
				result[i][j] = -1;
		}
	}

	/*
	ġ�� �ִ밪 ǥ�� ���
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << result[i][j] << " ";
		}
		cout << endl;
	}
	*/

	return result[0][8];
}

int max(int a, int b)
{
	if (a >= b)
		return a;
	else
		return b;
}