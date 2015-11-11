#include<iostream>
#include<string>
#include<cstdio>
using namespace std;

/*
 * 题目明义上是给定一个大数p,要求找出hanoi sequence该位置的数
 * 但因为数字过于庞大,采用递归去模拟肯定会超时
 *
 * 所以需要从题目给出的信息去找出hanoi sequence数字出现的规律
 * n = 1: 1
 * n = 2: 121
 * n = 3: 1213121
 * n = 4: 121312141213121
 * .
 * ..
 * ...
 * n = n: (n = n-1) n (n = n-1)
 * n = n+1: f(n-1) n f(n-1) n+1 f(n-1) n f(n-1)
 * 当n=n+1时,可以得知n出现的位置为2^(n-1)、3*2^(n-1)
 * 当n=n+2时,同理可知n出现的位置为2^(n-1)、3*2^(n-1)、5*2^(n-1)、7*2^(n-1)
 * 可知n出现的位置为2^(n-1)的奇数倍,这在2进制中表现为    xxxxx  1  00000...
 *                                            第n位
 * 例如:1出现在1、3、5、7、9
 *     2出现在2、6、10、14
 *     3出现在4、12...
 * 所以给定一个p,我们只需要把它转化成2进制,甚至不需要完全转化而只需要找道它的二进制表示中从后往前第一个为1的位置号
 */

int count = 0;
bool flag = false;
/*
 * 将长字符串转化为2进制,模拟除法过程
 */
string divide(string s, int divisor) {
	string quotient;
	int reminder = 0;
	//画个除法图,过程自然清楚
	for (int i = 0; i < s.length(); i++) {
		int dividend = (reminder * 10 + (s[i]-'0'));
		reminder = dividend % divisor;
		quotient += dividend/divisor + '0';
	}
	//用于统计遇到第一个1之前的0的个数
	count++;
	if (reminder == 1) flag = true;
	//得到的商第一位有可能为0,需要移除
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
