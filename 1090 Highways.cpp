#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

/*
 * 最小生成树,这里采用的是Prim算法,扩展点的集合
 *        另外还有Kruskal算法,是基于边的算法
 */

#define INF 9999999

int Map[505][505];
int dis[505];
int N;
bool vertex[505];

void Prim() {
	//首先将任意一个顶点加入顶点集合,这里总是选取第一个点
	vertex[1] = true;
    for (int i = 1; i <= N; i++) {
        dis[i] = Map[1][i];
    }
    //N个节点还需要扩展N-1次
    for (int i = 1; i < N; i++) {

        int min = INF, v;
        for (int j = 1; j <= N; j++) {
        	//寻找当前dis[1]~dis[N]中最小的距离,把对应顶点加入到vertex中
            if (!vertex[j] && dis[j] > 0 && dis[j] < min) {
                min = dis[j];
                v = j;
            }
        }
        vertex[v] = true;
        //更新当前所有不在顶点集合中的点到集合中的点的最小距离
        //Map[v][k] < dis[k]表示新加入顶点集合的节点到该点的距离小于之前集合中的点到该点的距离,更新距离(跟dijkstra算法类似)
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
        //初始化,因为题目保证1 <= Map[i][j] <= 65536,其实dis并不需要初始化
        for (int i = 1; i <= N; i++) {
        	dis[i] = INF;
            vertex[i] = false;
            for (int j = 1; j <= N; j++) {
                cin >> Map[i][j];
            }
        }
        Prim();

        sort(dis+1, dis+N+1);          //两个参数是左闭右开区间,不能写成sort(dis+1,dis+N)!!!
        cout << dis[N] << endl;
        if (T) cout << endl;
    }
}
