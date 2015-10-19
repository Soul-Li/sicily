#include<iostream>
#include<cstdio>

using namespace std;

/*
 * 模拟过程题,看懂题目就行了
 * N个孩子,每次老师吹一次哨子,每个孩子都把当前自己的糖果的一半分给右手边的孩子
 * 分完后,如果孩子的糖果数为奇数,那么老师会给孩子一块糖果使其糖果数变成偶数,然后再吹哨子
 * 游戏结束的条件是每个孩子的糖果数相同,输出游戏结束时老师吹哨子的次数和孩子最终的糖果数
 *
 * 题目有备注:游戏是一定会结束的
 * Notes:
 * The game ends in a finite number of steps because:
 * 1. The maximum candy count can never increase.
 * 2. The minimum candy count can never decrease.
 * 3. No one with more than the minimum amount will ever decrease to the minimum.
 * 4. If the maximum and minimum candy count are not the same, at least one student with the minimum amount must have their count increase
 */

//检查每个孩子的糖果数是否为偶数
bool check_equal(int A[], int n) {
	int standard = A[0];
	for (int i = 1; i < n; i++) {
		if (A[i] != standard) return false;
	}
	return true;
}

//模拟吹哨子的过程
void blow(int A[], int n) {
	int temp[n];
	for (int i = 0; i < n; i++) {
		temp[i] = A[i]/2;
		A[i] = temp[i];
	}
	for (int i = 0; i < n; i++) {
		if (i == 0) A[i] += temp[n-1];
		else A[i] += temp[i-1];
	}
}

//模拟老师给糖果
void if_odd(int A[], int n) {
	for (int i = 0; i < n; i++) {
		if (A[i] % 2 == 0) continue;
		A[i]++;
	}
}

int main() {
	int N;
	int Student[10000];
	while( cin >> N && N != 0) {
		int time = 0;
		bool equal = false;
		for (int i = 0; i < N; i++) {
			cin >> Student[i];
		}
		while (1) {
			equal = check_equal(Student, N);
			if (equal) break;
			blow(Student, N);
			if_odd(Student, N);
			time++;
		}
		cout << time << " " << Student[0] << endl;
	}
}
