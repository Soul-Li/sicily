#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

vector<int> vertex[105];           //顶点集合
int in[105], width[105];           //顶点的入度, width[i]表示深度为i时的宽度
bool visited[105], circle;         //是否被访问, 是否存在环
int Width, Depth;                  //最大的宽度, 最大的深度

//DFS
void next_level(int u, int d) {
	//检查是否有环存在
	if (visited[u]) {
		circle = true;
		return;
	}
	visited[u] = true;
	//实时更新最大深度
	if (d > Depth) Depth = d;
	//更新当前深度的宽度
	width[d]++;
	//实时更新最大宽度
	if (width[d] > Width) Width = width[d];

	for (int i = 0; i < vertex[u].size(); i++) {
		//继续搜索下一个子节点,深度+1
		next_level(vertex[u].at(i), d+1);
	}
}

int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) && n != 0) {
		Width = 0, Depth = 0;
		circle = false;
		//节点数==边数,必存在环
		if (m >= n) {
			circle = true;
		}
		//initialize
		for (int i = 0; i < 105; i++) {
			vertex[i].clear();
			in[i] = 0;
			width[i] = 0;
			visited[i] = false;
		}
		int u, v;
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &u, &v);
			vertex[u].push_back(v);
			in[v]++;
		}
		//对入度为0的点进行深搜
		for (int i = 1; i <= n; i++) {
			if (in[i] == 0) {
				next_level(i, 0);
			}
		}
		//如果一轮深搜完,还存在未访问过点,证明存在自环
		for (int i = 1; i <= n; i++) {
			if (!visited[i]) circle = true;
		}
		if (circle) cout << "INVALID\n";
		else cout << Depth << " " << Width << endl;
	}
}
