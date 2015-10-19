#include<iostream>
#include<cstdio>

/*
 * ����:A={a1, a2,..., an}(2<=n<=50000,|ai|<=10000)
               t1     t2
   d(A) = max{ ��ai + ��aj | 1 <= s1 <= t1 < s2 <= t2 <= n }
              i=s1   j=s2
           ����˼·:һ���˼·��ѡ��һ���ָ���,������ߺ��ұ���������Ӷκ���ӵ����ֵ,�������п��ܵķָ�ֵ�ҵ�d(A)
           �������һ��ķ���������������Ӷκ�,ʱ�临�Ӷ�ΪO(n^2),��Ȼ��TLE
            ���������������ӶκͲ��õ���dp����:
            dp[i] = max(dp[i-1]+num[i], num[i])  ����������������ұ�
            dp[i] = max(dp[i+1]+num[i], num[i])  �����������ұ������
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
		//����������ҵ�����Ӷκ�,fromLeft[i]��ʾ��num[i]Ϊ��β������Ӷκ�
		for (int i = 1; i <= n; i++) {
			scanf("%d", &num[i]);
			fromLeft[i] = max(fromLeft[i-1]+num[i], num[i]);
		}
		//����������������Ӷκ�,fromRight[i]��ʾ��num[i]Ϊ��β������Ӷκ�
		for (int i = n; i >= 1; i--) {
			fromRight[i] = max(fromRight[i+1]+num[i], num[i]);
		}

		int max = INF;
		//����fromLeft����,ʹ��fromLeft[i]��ʾ��1~i������Ӷκ�(�����Ӷο��Բ�����num[i])
		for (int i = 1; i <= n; i++) {
			if (fromLeft[i] > max) max = fromLeft[i];
			else fromLeft[i] = max;
		}
		max = INF;
		//����fromRight����,ʹ��fromRight[i]��ʾ��n~i������Ӷκ�(�����Ӷο��Բ�����num[i])
		for (int i = n; i >= 1; i--) {
			if (fromRight[i] > max) max = fromRight[i];
			else fromRight[i] = max;
		}

		max = INF;
		//����d(A)
		for (int i = 1; i <= n-1; i++) {
			if (fromLeft[i]+fromRight[i+1] > max) max = fromLeft[i]+fromRight[i+1];
		}
		printf("%d\n", max);
	}
}



