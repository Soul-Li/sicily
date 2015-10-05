/*
 * 1006 Team Rankings.cpp
 *
 *  Created on: 2015年9月29日
 *      Author: ABCD
 */
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
/*
 * 题目大意:“ABCDE”5个字母的随机排列为一个Ranking,给定n个排列
 *       定义任意两个ranking的distance为 字母对(AB,AC,AD,AE...)在两个ranking中的先后顺序不同的数量之和
 *       具体示例请看题目
 * 解题思路:
 *       对于给定的n个ranking,从'ABCDE'遍历到'EDCBA'(使用next_permutation函数,原理自己查)
 *       分别对n个ranking中的每个ranking计算distance再求和,保持一个最小值median和对应的median_ranking
 */

using namespace std;
string ranking[101];

//计算dis的方式
int cal_dis(string s1, string s2) {
	int pos1[5][5], pos2[5][5];
	int dif = 0;
	//存储字母出现的先后顺序的pos数组,pos[n][m] (n:A=0,B=1,C=2,D=3,E=4; m同上)
	//pos[n][m] = 1 表示 n在m前面(下标较小); pos[n][m] = -1 表示 n在m后面
	//这里j=i+1保证了不计算对角线(即n==m)的情况;
	//另外pos矩阵有个特性:即关于对角线对称的元素互为相反数,即pos[n][m] = -1*pos[m][n]
	for (int i = 0; i < s1.length(); i++) {
		for (int j = i+1; j < s1.length(); j++) {
			pos1[s1[i]-'A'][s1[j]-'A'] = (i < j) ? 1 : -1;
			pos2[s2[i]-'A'][s2[j]-'A'] = (i < j) ? 1 : -1;
			pos1[s1[j]-'A'][s1[i]-'A'] = -1*(pos1[s1[i]-'A'][s1[j]-'A']);
			pos2[s2[j]-'A'][s2[i]-'A'] = -1*(pos2[s2[i]-'A'][s2[j]-'A']);
		}
	}
	//计算dis,如果pos1[n][m] != pos2[n][m]则表示在这两个ranking中n与m的先后顺序不同
	for (int i = 0; i < s1.length(); i++) {
		for (int j = 0; j < s1.length(); j++) {
			if (i == j) continue;
			if (pos1[i][j] != pos2[i][j]) dif++;
		}
	}
	//存在重复计算,需要将结果除以2(n=1,m=2与n=2,m=1等等)
	return dif/2;
}

int main() {
	int n;
	while (scanf("%d", &n) && n != 0) {
		for (int i = 0; i < n; i++) {
			cin >> ranking[i];
		}
		int sum, median = 9999;
		string median_ranking, s = "ABCDE";
		do {
			sum = 0;
			for (int i = 0; i < n; i++) {
				sum += cal_dis(ranking[i], s);
			}
			if (sum < median) {
				median = sum;
				median_ranking = s;
			}
		} while(next_permutation(s.begin(), s.end()));   //next_permutation()函数,可以生成全排列
		cout << median_ranking << " is the median ranking with value " << median << "." << endl;
	}
}
