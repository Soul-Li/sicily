/*
 * 1024 Magic Island.cpp
 *
 *  Created on: 2015年10月1日
 *      Author: ABCD
 */
#include<iostream>
#include<vector>
#include<cstdio>
using namespace std;

/*
 * 树的遍历,求某点与能到达的最远节点的距离
 * 简单的深搜加回溯
 */

#define MAX 10001

//用于表示路径的节点,包括起点,终点和距离
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
int maxDis = 0;           //用于存储最长路径长度的全局变量

void DFS(int start, int sum_dis) {
	//从start出发的各条路径,深搜,注意回溯
	for (int i = 0; i < Map[start].size(); i++) {
		if (!visited[Map[start].at(i).to]) {
			visited[Map[start].at(i).to] = true;
			sum_dis += Map[start].at(i).dis;
			//更新最大长度
			if (sum_dis > maxDis)
				maxDis = sum_dis;

			DFS(Map[start].at(i).to, sum_dis);
			//回溯
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
			//双向路径,两边都可以走
			Map[f].push_back(Node(f, t, d));
			Map[t].push_back(Node(t, f, d));
		}
		visited[K] = true;
		DFS(K, 0);
		cout << maxDis << endl;
	}
}


