#include<iostream>
#include<cstdio>

/*
 * 题意:A={a1, a2,..., an}(2<=n<=50000,|ai|<=10000)
               t1     t2
   d(A) = max{ ∑ai + ∑aj | 1 <= s1 <= t1 < s2 <= t2 <= n }
              i=s1   j=s2
           解题思路:一般的思路是选定一个分隔线,计算左边和右边最大连续子段和相加的最大值,遍历所有可能的分割值找到d(A)
           如果采用一般的方法计算最大连续子段和,时间复杂度为O(n^2),显然会TLE
            这里计算最大连续子段和采用的是dp方法:
            dp[i] = max(dp[i-1]+num[i], num[i])  ————从左边往右边
            dp[i] = max(dp[i+1]+num[i], num[i])  ————从右边往左边
 */

using namespace std;
#define MAX 50000
#define INF -10001;

int num[MAX+1];
int fromLeft[MAX+1];
int fromRight[MAX+1];

int main() {
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);

		fromLeft[0] = 0;
		fromRight[n+1] = 0;
		//计算从左往右的最大子段和,fromLeft[i]表示以num[i]为结尾的最大子段和
		for (int i = 1; i <= n; i++) {
			scanf("%d", &num[i]);
			fromLeft[i] = max(fromLeft[i-1]+num[i], num[i]);
		}
		//计算从右往左的最大子段和,fromRight[i]表示以num[i]为结尾的最大子段和
		for (int i = n; i >= 1; i--) {
			fromRight[i] = max(fromRight[i+1]+num[i], num[i]);
		}

		int max = INF;
		//更新fromLeft数组,使得fromLeft[i]表示从1~i的最大子段和(这里子段可以不包括num[i])
		for (int i = 1; i <= n; i++) {
			if (fromLeft[i] > max) max = fromLeft[i];
			else fromLeft[i] = max;
		}
		max = INF;
		//更新fromRight数组,使得fromRight[i]表示从n~i的最大子段和(这里子段可以不包括num[i])
		for (int i = n; i >= 1; i--) {
			if (fromRight[i] > max) max = fromRight[i];
			else fromRight[i] = max;
		}

		max = INF;
		//计算d(A)
		for (int i = 1; i <= n-1; i++) {
			if (fromLeft[i]+fromRight[i+1] > max) max = fromLeft[i]+fromRight[i+1];
		}
		printf("%d\n", max);
	}
}



