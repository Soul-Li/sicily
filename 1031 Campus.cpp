#include<iostream>
#include<string>
#include<cstring>
#include<map>
#include<cstdio>

/*
 * 单源最短路径问题,难点在于节点是用字符串表示,因此这里用map来完成地点到抽象下标的映射
 * 另外题目有个深坑,就是最后要求最短路径的两个地点有可能未在前面的map中出现过,此时还需要分2种情况:
 *     ①两个地点名字相同,输出0
 *     ②两个地点名字不同,输出-1
 * 因此只有当两个地点均出现在之前的map映射中时,才按照正常的dijkstra算法进行计算
 *
 */

using namespace std;
#define MAX 999999

int Matrix[210][210];
bool visited[210];
int dis[210];
int node_num;

int shortest_dis(int from, int to) {
	//初始化
	for (int i = 0; i < node_num; i++) {
		if (Matrix[from][i] >= 0) {
			dis[i] = Matrix[from][i];
		} else {
			dis[i] = MAX;
		}
		visited[i] = false;
	}
	dis[from] = 0;
	visited[from] = true;

	//除开起始点,还需要n-1次遍历
	for (int i = 1; i < node_num; i++) {
		int u = -1, min = MAX;

		for (int j = 0; j < node_num; j++) {
			if (!visited[j] && dis[j] < min) {
				min = dis[j];
				u = j;
			}
		}
		if (u != -1) {
			visited[u] = true;
			//对所有在顶点集合外的点重新计算dis
			for (int k = 0; k < node_num; k++) {
				if (!visited[k] && Matrix[u][k] >= 0 && min+Matrix[u][k] < dis[k])
					dis[k] = min+Matrix[u][k];
			}
		}
	}
	//最后判断dis[to]是否得到更新,是则输出dis[to],否则输出-1
	if (dis[to] == MAX) return -1;
	else return dis[to];
}

int main() {
	int C, N;
	map<string, int> mapping;
	scanf("%d", &C);
	while (C--) {

		memset(Matrix, -1, sizeof(Matrix));
		scanf("%d", &N);
		string start, to;
		int dis;
		node_num = 0;

		for (int i = 0; i < N; i++) {
			cin >> start >> to >> dis;
			//统计节点数量
			if (!mapping.count(start))          //count(start)判断start是否在map中出现过
				mapping[start] = node_num++;
			if (!mapping.count(to))
				mapping[to] = node_num++;

			Matrix[mapping[start]][mapping[to]] = dis;
			Matrix[mapping[to]][mapping[start]] = dis;
		}

		cin >> start >> to;
		//映射只在这里起作用,把字符串下标转化成正常的数字下标,根本思想仍是最短路径
		if (mapping.count(start) && mapping.count(to)) {
			cout << shortest_dis(mapping[start], mapping[to]) << endl;
		} else if (start == to) {
			cout << "0" << endl;
		} else {
			cout << "-1" << endl;
		}
		mapping.clear();
	}
}

