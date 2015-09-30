#include<iostream>
#include<cstring>
#include<cstdio>

using namespace std;

int n, m, d;
bool isPrime[10000];
bool selected[1010];
int answer[1010];
bool finish;
//筛法素数表
void Prime() {
	memset(isPrime, true, sizeof(isPrime));
	isPrime[0] = isPrime[1] = false;
	//为什么此处可以用i*i<=10000(减少一半时间)? 因为在内循环中可以看出,当i较小时,j已经取了10000/i之后的那些值
	for (int i = 2; i * i <= 10000; i++) {
		if (isPrime[i]) {
			for (int j = 2; j <= 10000/i; j++) {
				isPrime[j*i] = false;
			}
		}
	}
}


//从后往前求和比较合理
bool check_sum(int pos, int val) {
	/*
	 * i = pos-1 >= 0表示至少pos>=1也即至少2个数字
	 * i >= pos-d+1 画图可知,从pos到i最多d个数字
	 * 技巧:从后往前求和,每多一个数字只需要一次循环搞定
	 * 如果每次从前往后求和,过程会很复杂
	 */
	for (int i = pos-1; i >= 0 && i >= pos-d+1; i--) {
		val += answer[i];
		if(isPrime[val]) return false;
	}
	return true;
}

void dfs(int pos) {
	for (int i = n; i <= m; i++) {
		if (!selected[i] && check_sum(pos, i)) {
			selected[i] = true;
			answer[pos] = i;
			//表示填完了所有数字
			if (pos == m-n) {
				finish = true;
				return;
			}
			//填下一位的数字
			dfs(pos+1);
			if (finish) return;
			//回溯,将填过的数字selected设为false,继续for循环
			//如果for循环终止还没有填完
			//说明上一级的数字填的不对
			//那么将跳到上一级的dfs(pos+1)处
			//如此就完成了整个深搜
			selected[i] = false;
		}
	}
}

int main() {
	Prime();
	while(1) {
		cin >> n >> m >> d;
		if (n == 0 && m == 0 && d == 0) break;
		memset(selected, false, sizeof(selected));
		finish = false;
		dfs(0);
		if (finish) {
			printf("%d", answer[0]);
			for (int i = 1; i <= m-n; i++) {
				printf(",%d", answer[i]);
			}
			printf("\n");
		} else {
			printf("No anti-prime sequence exists.\n");
		}
	}
}
