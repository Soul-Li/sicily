#include<iostream>
#include<cstring>
using namespace std;

/*
 * 解题思路:动态规划
 * 因为P1的取牌方式只有2种,左边或者右边,而P2的行为已知,剩余的两边哪边数字大取哪边,相同则取左边的.
 * 所以状态转移方程:
 *                       左边　>=　右边　　　　　　　　右边　＞　左边
 * ①左边:
 *     begin~end  ---> (begin+2,end)   or (begin+1,end-1)
 * ②右边:
 *     begin~end  ---> (begin+1,end-1) or (begin, end-2)
 * 结束条件:
 *     end-begin = 2, 此时直接取两者中较大的数即可
 */

int cards[1001];
int maxSum[1001][1001];
int choose(int begin, int end) {
	if (begin > end) return 0;

	if (maxSum[begin][end] != -1)
		return maxSum[begin][end];

	if (begin+1 == end) {
		maxSum[begin][end] = ((cards[begin] > cards[end]) ? cards[begin] : cards[end]);
		return maxSum[begin][end];
	}

	int chleft = 0;
	//取左边第一张,即cards[begin]          模拟P2选牌,若左2>右1,则下轮区间为左3到右1，否则为左2到右2
	chleft = chleft + cards[begin] + ((cards[begin+1] >= cards[end]) ? choose(begin+2, end) : choose(begin+1, end-1));

	int chright = 0;
	//错误之处:
	//chright = chright + cards[end] + ((cards[end-1] >= cards[begin]) ? choose(begin, end-2) : choose(begin+1, end-1));
	//因为当左等于右时,P2的贪婪算法默认取左边，所以正确写法如下:
	chright = chright + cards[end] + ((cards[begin] >= cards[end-1]) ? choose(begin+1, end-1) : choose(begin, end-2));

	maxSum[begin][end] = (chleft > chright) ? chleft : chright;
	return maxSum[begin][end];
}

int main() {
	int n, t = 1;
	while (cin >> n && n) {
		int sum = 0;
		memset(maxSum, -1, sizeof(maxSum));
		for (int i = 0; i < n; i++) {
			cin >> cards[i];
			sum += cards[i];
		}
		int p1 = choose(0, n-1);
		int p2 = sum-p1;
		cout << "In game " << t << ", the greedy strategy might lose by as many as ";
		cout << ((p1>p2)?(p1-p2):(p2-p1)) << " points." << endl;
		t++;
	}
}
