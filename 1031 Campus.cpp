#include<iostream>
#include<string>
#include<cstring>
#include<map>
#include<cstdio>

/*
 * ��Դ���·������,�ѵ����ڽڵ������ַ�����ʾ,���������map����ɵص㵽�����±��ӳ��
 * ������Ŀ�и����,�������Ҫ�����·���������ص��п���δ��ǰ���map�г��ֹ�,��ʱ����Ҫ��2�����:
 *     �������ص�������ͬ,���0
 *     �������ص����ֲ�ͬ,���-1
 * ���ֻ�е������ص��������֮ǰ��mapӳ����ʱ,�Ű���������dijkstra�㷨���м���
 *
 */

using namespace std;
#define MAX 999999

int Matrix[210][210];
bool visited[210];
int dis[210];
int node_num;

int shortest_dis(int from, int to) {
	//��ʼ��
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

	//������ʼ��,����Ҫn-1�α���
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
			//�������ڶ��㼯����ĵ����¼���dis
			for (int k = 0; k < node_num; k++) {
				if (!visited[k] && Matrix[u][k] >= 0 && min+Matrix[u][k] < dis[k])
					dis[k] = min+Matrix[u][k];
			}
		}
	}
	//����ж�dis[to]�Ƿ�õ�����,�������dis[to],�������-1
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
			//ͳ�ƽڵ�����
			if (!mapping.count(start))          //count(start)�ж�start�Ƿ���map�г��ֹ�
				mapping[start] = node_num++;
			if (!mapping.count(to))
				mapping[to] = node_num++;

			Matrix[mapping[start]][mapping[to]] = dis;
			Matrix[mapping[to]][mapping[start]] = dis;
		}

		cin >> start >> to;
		//ӳ��ֻ������������,���ַ����±�ת���������������±�,����˼���������·��
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

