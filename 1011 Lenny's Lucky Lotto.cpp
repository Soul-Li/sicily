#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

/*
 * ��̬�滮: p[i][j]��ʾ����Ϊi��βΪj������(i<jʱp[i][j]=0)
 * ��ʼ״̬: p[1][k](1<=k<=2000)��Ϊ1
 * ״̬ת�Ʒ���: ��i>=2ʱ,p[i][j] = sum(p[i-1][k])(i-1 <= k <= j/2)
 * ���ս��: p[N][M] = sum(p[N][N]+p[N][N+1]+...+p[N][M])
 * ��Ҫע�����:���ս�����ܻ�ǳ���,���ʹ��unsigned long long�����Ǳ�Ҫ��
 */

#define MAXN 10
#define MAXM 2000

unsigned long long p[MAXN+1][MAXM+1];

int main() {
	memset(p, 0, sizeof(p));
	//Ԥ��������п����õ���ֵ
	for (int i = 1; i <= MAXM; i++) {
		p[1][i] = 1;
	}
	for (int i = 2; i <= MAXN; i++) {
		for (int j = i; j <= MAXM; j++) {
			for (int k = i-1; k <= j/2; k++) {
				p[i][j] += p[i-1][k];
			}
		}
	}

	int C, N, M, time = 0;
	unsigned long long result;
	scanf("%d", &C);
	while (C--) {
		time++;
		result = 0;
		scanf("%d %d", &N, &M);
		//�������ս��
		for (int i = N; i <= M; i++) {
			result += p[N][i];
		}
		printf("Case %d: n = %d, m = %d, # lists = %lld\n", time, N, M, result);
	}
	return 0;
}