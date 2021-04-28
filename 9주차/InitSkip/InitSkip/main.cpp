#include <iostream>
using std::cout; using std::cin;  using std::endl;
void InitSkip(char p[], int skip[]);
int mischar(char p[], char t[], int skip[]);
int index(char a);
int main()
{
	cout << "12171856 �ֿ�� ������° �ǽ� ����" << endl;
	cout << "Text�� Pattern�� ��ġ�ϴ� ��ġ ���" << endl;
	char pattern[6] = "ATION";
	//����
	//�ؽ�Ʈ
	char text[51] = "VISION QUESTION ONION CAPTION GRADUATION EDUCATION";
	int skip[27];
	//skip�迭�� 26�� ���ĺ� + space�ؼ� 27��
	
	int pos = 0;
	//mischar�� return�ϴ°��� ������ pos
	int M = strlen(pattern);
	int	N = strlen(text);
	//�Լ���, main���� ���������� M�� ������ ����, N�� text�� ����
	int k = 0;
	//k�� pos + M ���� �뵵
	//pos�� ���� mischar���� ������ ã�Ƴ´ٸ� ���� ~ ���� + ���ϱ��̸�ŭ�� �̹� �˻��� ���� �̹Ƿ� pos + M���� �����Ѱ� k
	while (1)
		//���ѷ���
	{
		pos = mischar(pattern, text + k, skip);
		//pos�� ������ �˻��� �κ� ���ĺ��� �ٽ� ����
		pos += k;
		//k (������ pos + M)���� ���� pos�� ���ؾ� ��ġ�� ��Ȯ�� �� �� �ִ�
		k = pos + M;
		if (k <= N)
		//k�� N���� �۰ų� ������ �� ������ text���κ� ���� ����������
		{
			cout << "������ �߻��� ��ġ: " << pos << endl;
			//pos�� (������ �߻��� ��ġ)�� ���
		}
		else 
		//k�� N���� ũ�� text ���� ������̹Ƿ� break�ؼ� ���ѷ��� ��
			break;
	}
}
void InitSkip(char p[],int skip[])
//skip �迭�� ������ִ� �Լ�
{
	int i;
	int M = strlen(p);
	for (i = 0; i < 27; i++)
	{
		skip[i] = M;
		//���Ͽ� ���� ���ڸ� ���� ���ڿ� ���̸�ŭ skip
	}
	for (i = 0; i < M; i++)
	{
		skip[index(p[i])] = M - i - 1;
		//���Ͽ� �ִ� ���ڸ� ������ ���� �� ���ڿ��� �Ÿ���ŭ skip
	}
	//���⼭ ������� skip�迭�� 0(A)��° 4, 19(T)��° 3, 8(I)��° 2, 14(O)��° 1, 13(N)��° 0�̰� ������ ����(space����)���� 5�� ���̴�.
}
int mischar(char p[], char t[], int skip[]) 
{
	int i, j, k;
	int M = strlen(p);
	int	N = strlen(t);


	InitSkip(p,skip);
	
	for (i = M - 1, j = M - 1; j >= 0; --i, --j) 
		//���ڿ� ���������� ��
	{
		while (t[i] != p[j]) 
			//�����̶� �ؽ�Ʈ�� �ٸ���
		{
			k = skip[index(t[i])];
			//k�� skip�迭 �ȿ� �ִ� ������ �ο�
			//���� ���ڰ� ���� �ȿ� �ִ� ������ �ϳ��� skip�迭�� ���ִ� �ش�Ǵ� ������ ��
			//���ڰ� ���� �ȿ� ������ ������ ������ 5�� �ο���
			if (M - j > k)
				//������ ���� - j�� k���� ũ�� 
			{
				i = i + M - j;
				//���� ���� - ���ؼ� ������ ��ŭ ���������� ���� ��
			}
			else
				//�׷��� ������ k��ŭ ���������� ���� ��
			{
				i = i + k;
			}
			if (i >= N)	return N;
			//�̷��� �ϴٰ� ������ �񱳸� �Ϸ��ϸ� N�� return
			j = M - 1;
			//���Ƽ� �������� ��� ���ϰԵǸ� j�� --�Ǿ����ٵ� �׷��ٰ� �ٸ����� ������ �ٽ� j�� M-1�� �ʱ�ȭ ����ߵȴ�
		}
		
	}
	return i + 1;
	//��ġ�Ǵ� �κ��� ã���� for���� ����� ����� ����
	//i+1�� ��ġ�ϴ� ���ۺκ��̴ϱ� i+1�� return
}
int index(char a)
//skip�迭���� �̿��Ұ�
//A��0��° B�� 1��° �̷������� �̿��ϱ� ����
//�빮�ڸ� ����Ұ��̹Ƿ� A == 65 �̴ϱ� -65�� ���ش�
//space�� ó������ߵǴµ� �ƽ�Ű�ڵ�� 32���̹Ƿ� 32�� 27��° ���ĺ��̶� �����Ұ��̹Ƿ� 26�� ����
{
	if (a == 32)
	{
		return 26;
	}
	else
	{
		return a - 65;
	}
}