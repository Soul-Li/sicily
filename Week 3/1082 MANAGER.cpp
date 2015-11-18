/*
 * main1.cpp
 *
 *  Created on: 2015年11月17日
 *      Author: ABCD
 */
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<vector>

/*
 * 题意:
 *    5            ————Cost上界
 *    2            ————removeList的大小
 *    1 3          ————removedList的内容,指定move第几个process时需要输出其cost
 *    a 2          ----\
 *    a 3               \
 *    r                  \
 *    a 4                 \表示一系列操作，主要有a(添加进程),r(移除进程),p(设置移除模式,1--移除最小的、2--移除最大的,默认刚开始为1)
 *    p 2                 /
 *    r                  /
 *    a 5               /
 *    r            ----/
 *    e            ————————表示输入结束
 *
 * 解法:
 *    建立一个进程的数组,下标表示cost,值表示cost为此值的进程数
 *    维护这些参数: processNum
 *              removeNum
 *              minIndex           ——当前process中最小的cost
 *              maxIndex           ——当前process中最大的cost
 */

using namespace std;

int process[10010];
int processNum, removeNum, minIndex, maxIndex, index;
bool choosemin;
void updateIndex() {
	int tempMin = minIndex, tempMax = maxIndex;
	minIndex = 10010, maxIndex = 0;
	for (int i = tempMin; i <= tempMax; i++) {
		if (process[i]) {
			minIndex = i;
			break;
		}
	}
	for (int i = tempMax; i >= tempMin; i--) {
		if (process[i]) {
			maxIndex = i;
			break;
		}
	}
}

int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int maxCost, len, T = 0;
	while (scanf("%d", &maxCost) != EOF) {
		//题目输出要求输出样例间隔一个空行
		if (T >= 1) printf("\n");
		T++;
		for (int i = 1; i <= maxCost; i++) {
			process[i] = 0;
		}
		scanf("%d", &len);
		int removeList[len+1];
		int temp;
		for (int i = 0; i < len; i++) {
			scanf("%d", &removeList[i]);
		}
		char op;
		choosemin = true;
		processNum = 0, removeNum = 0, minIndex = 10010, maxIndex = 0, index = 0;

		while (1) {
			cin >> op;
			if (op == 'a') {
				cin >> temp;
				if (temp < minIndex) minIndex = temp;
				if (temp > maxIndex) maxIndex = temp;
				process[temp]++;
				processNum++;
			} else if (op == 'r') {
				//如果当前进程数为0
				if (processNum == 0) {
					printf("-1\n");
					continue;
				}

				processNum--;
				removeNum++;
				//根据当前模式去决定是移除最小还是最大
				if (choosemin) {
					process[minIndex]--;
					//如果满足移除的是removeList指定的那些个数
					if (removeNum == removeList[index]) {
						printf("%d\n", minIndex);
						index++;
					}
					//当前最小的为0,则需要更新minIndex,有可能也需要同时更新maxIndex(processNum为1)
					if (process[minIndex] == 0) updateIndex();

				} else {
					process[maxIndex]--;
					if (removeNum == removeList[index]) {
						printf("%d\n", maxIndex);
						index++;
					}

					if (process[maxIndex] == 0) updateIndex();
				}
			} else if (op == 'p') {
				cin >> temp;
				// 该开始写错了,导致choosemin模式切换出去之后切换不回来
				// if (temp == 1) continue;
				if (temp == 1) choosemin = true;
				if (temp == 2) choosemin = false;
			} else if (op == 'e') {
				break;
			}
		}
	}
}
