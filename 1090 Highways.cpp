#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

/*
 * ��С������,������õ���Prim�㷨,��չ��ļ���
 *        ���⻹��Kruskal�㷨,�ǻ��ڱߵ��㷨
 */

#define INF 9999999

int Map[505][505];
int dis[505];
int N;
bool vertex[505];

void Prim() {
	//���Ƚ�����һ��������붥�㼯��,��������ѡȡ��һ����
	vertex[1] = true;
    for (int i = 1; i <= N; i++) {
        dis[i] = Map[1][i];
    }
    //N���ڵ㻹��Ҫ��չN-1��
    for (int i = 1; i < N; i++) {

        int min = INF, v;
        for (int j = 1; j <= N; j++) {
        	//Ѱ�ҵ�ǰdis[1]~dis[N]����С�ľ���,�Ѷ�Ӧ������뵽vertex��
            if (!vertex[j] && dis[j] > 0 && dis[j] < min) {
                min = dis[j];
                v = j;
            }
        }
        vertex[v] = true;
        //���µ�ǰ���в��ڶ��㼯���еĵ㵽�����еĵ����С����
        //Map[v][k] < dis[k]��ʾ�¼��붥�㼯�ϵĽڵ㵽�õ�ľ���С��֮ǰ�����еĵ㵽�õ�ľ���,���¾���(��dijkstra�㷨����)
        for (int k = 1; k <= N; k++) {
            if (!vertex[k] && Map[v][k] < dis[k]) {
                dis[k] = Map[v][k];
            }
        }
    }
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        scanf("%d", &N);
        if (N < 3 || N > 500) break;
        //��ʼ��,��Ϊ��Ŀ��֤1 <= Map[i][j] <= 65536,��ʵdis������Ҫ��ʼ��
        for (int i = 1; i <= N; i++) {
        	dis[i] = INF;
            vertex[i] = false;
            for (int j = 1; j <= N; j++) {
                cin >> Map[i][j];
            }
        }
        Prim();

        sort(dis+1, dis+N+1);          //��������������ҿ�����,����д��sort(dis+1,dis+N)!!!
        cout << dis[N] << endl;
        if (T) cout << endl;
    }
}
