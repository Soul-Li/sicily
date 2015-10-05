/*
 * 1024 Magic Island.cpp
 *
 *  Created on: 2015��10��1��
 *      Author: ABCD
 */
#include<iostream>
#include<vector>
#include<cstdio>
using namespace std;

/*
 * ���ı���,��ĳ�����ܵ������Զ�ڵ�ľ���
 * �򵥵����Ѽӻ���
 */

#define MAX 10001

//���ڱ�ʾ·���Ľڵ�,�������,�յ�;���
struct Node {
	int from;
	int to;
	int dis;
	Node(int f, int t, int d) {
		from = f;
		to = t;
		dis = d;
	}
};
vector<Node> Map[MAX];
bool visited[MAX];
int maxDis = 0;           //���ڴ洢�·�����ȵ�ȫ�ֱ���

void DFS(int start, int sum_dis) {
	//��start�����ĸ���·��,����,ע�����
	for (int i = 0; i < Map[start].size(); i++) {
		if (!visited[Map[start].at(i).to]) {
			visited[Map[start].at(i).to] = true;
			sum_dis += Map[start].at(i).dis;
			//������󳤶�
			if (sum_dis > maxDis)
				maxDis = sum_dis;

			DFS(Map[start].at(i).to, sum_dis);
			//����
			sum_dis -= Map[start].at(i).dis;
			visited[Map[start].at(i).to] = false;
		}
	}
}

int main() {
	int N, K;
	while (scanf("%d %d", &N, &K) != EOF) {
		for (int i = 0; i < MAX; i++) {
			Map[i].clear();
			visited[i] = false;
		}
		maxDis = 0;
		for (int i = 1; i < N; i++) {
			int f, t, d;
			cin >> f >> t >> d;
			//˫��·��,���߶�������
			Map[f].push_back(Node(f, t, d));
			Map[t].push_back(Node(t, f, d));
		}
		visited[K] = true;
		DFS(K, 0);
		cout << maxDis << endl;
	}
}


