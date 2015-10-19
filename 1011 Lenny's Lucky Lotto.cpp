#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

/*
 * 动态规划: p[i][j]表示长度为i结尾为j的序列(i<j时p[i][j]=0)
 * 初始状态: p[1][k](1<=k<=2000)均为1
 * 状态转移方程: 当i>=2时,p[i][j] = sum(p[i-1][k])(i-1 <= k <= j/2)
 * 最终结果: p[N][M] = sum(p[N][N]+p[N][N+1]+...+p[N][M])
 * 需要注意的是:最终结果可能会非常大,因此使用unsigned long long类型是必要的
 */

#define MAXN 10
#define MAXM 2000

unsigned long long p[MAXN+1][MAXM+1];

int main() {
	memset(p, 0, sizeof(p));
	//预先算好所有可能用到的值
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
		//计算最终结果
		for (int i = N; i <= M; i++) {
			result += p[N][i];
		}
		printf("Case %d: n = %d, m = %d, # lists = %lld\n", time, N, M, result);
	}
	return 0;
}