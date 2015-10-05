#include<iostream>
#include<cstdio>

using namespace std;
/*
 * 类似24点的游戏,5个数（可以少于5个)通过一些运算(+ - * /),看能否得到目标树,不能的话输出可以得到的小于target的最大的数字
 *
 * 解法:深搜
 *     从当前所有数中随机取2个进行可能的所有运算(注意除法不能产生小数不能除0以及减法有2种情况)
 *     刚开始我采用的是vector,后来发现并不好用,iter处理起来很麻烦
 *     采用数组结构,我们可以将当前要运算的2个数字其中1个用第n-1位的数来覆盖,另外1个用来存储运算结果,然后在n-1长度的数组继续操作
 *
 */

#define inf -99999999;

int target;
int approach = inf;          //由于有可能有负数的结果产生,所遇approach不能初始化为0
int M[5];

//根据题意,approach不能超过target
void cal_approach(int n) {
	for (int i = 0; i < n; i++) {
		if (M[i] <= target && M[i] > approach)
			approach = M[i];
	}
}

void do_arithmetic(int n) {
	cal_approach(n);
	if (approach == target) return;
	if (n == 1) return;
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			int temp1 = M[i], temp2 = M[j];
			M[j] = M[n-1];

			M[i] = temp1+temp2;
			do_arithmetic(n-1);
			M[i] = temp1-temp2;
			do_arithmetic(n-1);
			M[i] = temp2-temp1;
			do_arithmetic(n-1);
			M[i] = temp1*temp2;
			do_arithmetic(n-1);
			if (temp2 != 0 && (temp1 % temp2 ==0)) {
				M[i] = temp1/temp2;
				do_arithmetic(n-1);
			}
			if (temp1 != 0 && (temp2 % temp1 ==0)) {
				M[i] = temp2/temp1;
				do_arithmetic(n-1);
			}
			//一轮运算完毕,回溯,进行下一轮for循环
			M[i] = temp1, M[j] = temp2;
		}
	}
}

int main() {
	int N;
	cin >> N;
	while (N--) {
		cin >> M[0] >> M[1] >> M[2] >> M[3] >> M[4] >> target;
		approach = inf;
		do_arithmetic(5);
		cout << approach << endl;
	}
}
