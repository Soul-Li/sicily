/*
 * main1.cpp
 *
 *  Created on: 2015��11��17��
 *      Author: ABCD
 */
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<vector>

/*
 * ����:
 *    5            ��������Cost�Ͻ�
 *    2            ��������removeList�Ĵ�С
 *    1 3          ��������removedList������,ָ��move�ڼ���processʱ��Ҫ�����cost
 *    a 2          ----\
 *    a 3               \
 *    r                  \
 *    a 4                 \��ʾһϵ�в�������Ҫ��a(��ӽ���),r(�Ƴ�����),p(�����Ƴ�ģʽ,1--�Ƴ���С�ġ�2--�Ƴ�����,Ĭ�ϸտ�ʼΪ1)
 *    p 2                 /
 *    r                  /
 *    a 5               /
 *    r            ----/
 *    e            ������������������ʾ�������
 *
 * �ⷨ:
 *    ����һ�����̵�����,�±��ʾcost,ֵ��ʾcostΪ��ֵ�Ľ�����
 *    ά����Щ����: processNum
 *              removeNum
 *              minIndex           ������ǰprocess����С��cost
 *              maxIndex           ������ǰprocess������cost
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
		//��Ŀ���Ҫ������������һ������
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
				//�����ǰ������Ϊ0
				if (processNum == 0) {
					printf("-1\n");
					continue;
				}

				processNum--;
				removeNum++;
				//���ݵ�ǰģʽȥ�������Ƴ���С�������
				if (choosemin) {
					process[minIndex]--;
					//��������Ƴ�����removeListָ������Щ����
					if (removeNum == removeList[index]) {
						printf("%d\n", minIndex);
						index++;
					}
					//��ǰ��С��Ϊ0,����Ҫ����minIndex,�п���Ҳ��Ҫͬʱ����maxIndex(processNumΪ1)
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
				// �ÿ�ʼд����,����chooseminģʽ�л���ȥ֮���л�������
				// if (temp == 1) continue;
				if (temp == 1) choosemin = true;
				if (temp == 2) choosemin = false;
			} else if (op == 'e') {
				break;
			}
		}
	}
}
