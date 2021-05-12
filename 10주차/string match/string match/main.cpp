#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define scan -1
#define TRUE 1
#define FALSE 0
#define size 100

struct Deque
{
	int* deque;
	int first, last;
};

struct Deque dq;
char ch[10] = { ' ','A',' ','B',' ', ' ', 'A','C','D',' ' };
int next1[10] = { 5,2,3,4,8,6,7,8,9,0 };
int next2[10] = { 5,2,1,4,8,2,7,8,9,0 };

void insertFirst(int v) { dq.deque[dq.first--] = v; }
void insertLast(int v) { dq.deque[++dq.last] = v; }
int deleteFirst() { dq.deque[dq.first] = 0; return dq.deque[++dq.first]; }
int isEmpty() { if (dq.first == dq.last) return TRUE; else return FALSE; }
int match(char* t)
{
	int n1, n2;
	int i, j = 0, k, N = strlen(t), state = next1[0];

	dq.deque = (int*)malloc(sizeof(int) * size);
	dq.first = size / 2; dq.last = size / 2;
	for (i = 0; i < size; i++) dq.deque[i] = 0;
	insertLast(scan);
	printf("%d[%d]\n", state, dq.deque[dq.first + 1]);

	while (state)
		//state가 0이 되면 종료
	{
		printf("state=%d\n", state);
		if (state == scan)
		{
			j++;
			if (isEmpty()) insertFirst(next1[0]);
			insertLast(scan);
		}
		else if (ch[state] == t[j])
		{
			insertLast(next1[state]);
		}
		else if (ch[state] == ' ')
		{
			n1 = next1[state]; n2 = next2[state];
			insertFirst(n1); if (n1 != n2) insertFirst(n2);
		}
		for (k = dq.first + 1; k <= dq.last; k++) printf("[%d]", dq.deque[k]);
		printf("\n");
		if (isEmpty()) return j;
		if (j > N) return 0;
		state = deleteFirst();
	}
	free(dq.deque);
	return j - 1;
}
int main()
{
	char text[100] = "CDAABCAAABDDACDAACAAAAAAABD";
	int N, pos, previous = 0, i = 0;

	N = strlen(text);
	while (1)
	{
		pos = match(text + i);
		if (pos == 0) break;
		pos += previous;
		i = pos;
		if (i <= N) printf("패턴이 발생한 위치 : %d\n", pos);
		else break;
		previous = i;
	}
	printf("패턴 매칭 종료.\n");
}