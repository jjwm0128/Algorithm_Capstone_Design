#include <iostream>
using std::cout; using std::cin;  using std::endl;
void InitSkip(char p[], int skip[]);
int mischar(char p[], char t[], int skip[]);
int index(char a);
int main()
{
	cout << "12171856 주우민 여덟번째 실습 과제" << endl;
	cout << "Text와 Pattern이 일치하는 위치 출력" << endl;
	char pattern[6] = "ATION";
	//패턴
	//텍스트
	char text[51] = "VISION QUESTION ONION CAPTION GRADUATION EDUCATION";
	int skip[27];
	//skip배열은 26개 알파벳 + space해서 27개
	
	int pos = 0;
	//mischar가 return하는것을 저장할 pos
	int M = strlen(pattern);
	int	N = strlen(text);
	//함수들, main에서 공통적으로 M은 패턴의 길이, N은 text의 길이
	int k = 0;
	//k는 pos + M 저장 용도
	//pos는 만약 mischar에서 패턴을 찾아냈다면 패턴 ~ 패턴 + 패턴길이만큼은 이미 검색된 상태 이므로 pos + M값을 저장한게 k
	while (1)
		//무한루프
	{
		pos = mischar(pattern, text + k, skip);
		//pos는 이전에 검색한 부분 이후부터 다시 시작
		pos += k;
		//k (이전의 pos + M)값에 현재 pos를 더해야 위치를 정확히 알 수 있다
		k = pos + M;
		if (k <= N)
		//k가 N보다 작거나 같으면 즉 패턴이 text끝부분 까지 존재했으면
		{
			cout << "패턴이 발생한 위치: " << pos << endl;
			//pos값 (패턴이 발생한 위치)을 출력
		}
		else 
		//k가 N보다 크면 text 밖을 벗어난것이므로 break해서 무한루프 끝
			break;
	}
}
void InitSkip(char p[],int skip[])
//skip 배열을 만들어주는 함수
{
	int i;
	int M = strlen(p);
	for (i = 0; i < 27; i++)
	{
		skip[i] = M;
		//패턴에 없는 문자면 패턴 문자열 길이만큼 skip
	}
	for (i = 0; i < M; i++)
	{
		skip[index(p[i])] = M - i - 1;
		//패턴에 있는 문자면 패턴의 끝과 그 문자와의 거리만큼 skip
	}
	//여기서 만들어진 skip배열은 0(A)번째 4, 19(T)번째 3, 8(I)번째 2, 14(O)번째 1, 13(N)번째 0이고 나머지 문자(space포함)들은 5가 값이다.
}
int mischar(char p[], char t[], int skip[]) 
{
	int i, j, k;
	int M = strlen(p);
	int	N = strlen(t);


	InitSkip(p,skip);
	
	for (i = M - 1, j = M - 1; j >= 0; --i, --j) 
		//문자열 끝에서부터 비교
	{
		while (t[i] != p[j]) 
			//패턴이랑 텍스트가 다르면
		{
			k = skip[index(t[i])];
			//k를 skip배열 안에 있는 값으로 부여
			//지금 문자가 패턴 안에 있는 문자중 하나면 skip배열에 들어가있는 해당되는 문자의 수
			//문자가 패턴 안에 없으면 패턴의 길이인 5가 부여됨
			if (M - j > k)
				//패턴의 길이 - j가 k보다 크면 
			{
				i = i + M - j;
				//패턴 길이 - 비교해서 맞은거 만큼 오른쪽으로 가서 비교
			}
			else
				//그렇지 않으면 k만큼 오른쪽으로 가서 비교
			{
				i = i + k;
			}
			if (i >= N)	return N;
			//이렇게 하다가 끝까지 비교를 완료하면 N을 return
			j = M - 1;
			//같아서 왼쪽으로 계속 비교하게되면 j가 --되었을텐데 그러다가 다른것을 만나면 다시 j를 M-1로 초기화 해줘야된다
		}
		
	}
	return i + 1;
	//일치되는 부분을 찾으면 for문을 벗어나서 여기로 나옴
	//i+1이 일치하는 시작부분이니까 i+1을 return
}
int index(char a)
//skip배열에서 이용할거
//A는0번째 B는 1번째 이런식으로 이용하기 위함
//대문자만 사용할것이므로 A == 65 이니까 -65를 해준다
//space도 처리해줘야되는데 아스키코드로 32번이므로 32면 27번째 알파벳이라 생각할것이므로 26을 리턴
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