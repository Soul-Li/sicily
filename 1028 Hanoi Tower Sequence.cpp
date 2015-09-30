#include<iostream>
#include<string>
#include<cstdio>
using namespace std;

/*
 * ��Ŀ�������Ǹ���һ������p,Ҫ���ҳ�hanoi sequence��λ�õ���
 * ����Ϊ���ֹ����Ӵ�,���õݹ�ȥģ��϶��ᳬʱ
 *
 * ������Ҫ����Ŀ��������Ϣȥ�ҳ�hanoi sequence���ֳ��ֵĹ���
 * n = 1: 1
 * n = 2: 121
 * n = 3: 1213121
 * n = 4: 121312141213121
 * .
 * ..
 * ...
 * n = n: (n = n-1) n (n = n-1)
 * n = n+1: f(n-1) n f(n-1) n+1 f(n-1) n f(n-1)
 * ��n=n+1ʱ,���Ե�֪n���ֵ�λ��Ϊ2^(n-1)��3*2^(n-1)
 * ��n=n+2ʱ,ͬ���֪n���ֵ�λ��Ϊ2^(n-1)��3*2^(n-1)��5*2^(n-1)��7*2^(n-1)
 * ��֪n���ֵ�λ��Ϊ2^(n-1)��������,����2�����б���Ϊ    xxxxx  1  00000...
 *                                            ��nλ
 * ����:1������1��3��5��7��9
 *     2������2��6��10��14
 *     3������4��12...
 * ���Ը���һ��p,����ֻ��Ҫ����ת����2����,��������Ҫ��ȫת����ֻ��Ҫ�ҵ����Ķ����Ʊ�ʾ�дӺ���ǰ��һ��Ϊ1��λ�ú�
 */

int count = 0;
bool flag = false;
/*
 * �����ַ���ת��Ϊ2����,ģ���������
 */
string divide(string s, int divisor) {
	string quotient;
	int reminder = 0;
	//��������ͼ,������Ȼ���
	for (int i = 0; i < s.length(); i++) {
		int dividend = (reminder * 10 + (s[i]-'0'));
		reminder = dividend % divisor;
		quotient += dividend/divisor + '0';
	}
	//����ͳ��������һ��1֮ǰ��0�ĸ���
	count++;
	if (reminder == 1) flag = true;
	//�õ����̵�һλ�п���Ϊ0,��Ҫ�Ƴ�
	if (quotient[0] == '0') {
		quotient.erase(quotient.begin());
	}
	return quotient;
}

int main() {
	int T, n = 1;
	scanf("%d", &T);
	while (T--) {
		string p;
		cin >> p;
		while (!p.empty()) {
			p = divide(p, 2);
			if (flag) break;
		}
		printf("Case %d: %d\n", n, count);
		if (T > 0) printf("\n");
		count = 0;
		flag = false;
		n++;
	}
}
