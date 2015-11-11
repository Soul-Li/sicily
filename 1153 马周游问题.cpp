#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
/*
 * 优化搜索,建立代价函数nasc()来改进搜索策略,保证每次找的下一步都是当前最应该去搜索的点
 */


using namespace std;

//定义马走的8个方向的二维数组,从(x-2,y-1)顺时针直到(x-2,y+1)
int dir[8][2] = {-2,-1, -1,-2, 1,-2, 2,-1, 2,1, 1,2, -1,2, -2,1};
//判断棋盘上的格子是否被走过
bool visit[64];
//存储马走的路线
int route[64];

//判断马是否跳出棋盘外
bool out_of_map(int x, int y) {
	if (x < 0 || x > 7 || y < 0 || y > 7) return true;
	return false;
}

//计算当前马所处位置走下一步的合法位置的数量
int nasc(int x, int y) {
	int count = 0;
	for (int i = 0; i < 8; i++) {
		int X = x+dir[i][0];
		int Y = y+dir[i][1];
		if (!out_of_map(X, Y) && !visit[X*8+Y]) count++;
	}
	return count;
}

//x,y代表当前坐标,next_available_step_count代表下一步可走的合法位置数量
struct Node {
	int x;
	int y;
	int next_available_step_count;
	Node(int X, int Y) {
		x = X;
		y = Y;
		next_available_step_count = nasc(X, Y);
	}
};

//排序函数,按照每个节点的下一步合法数目从低到高排序
bool cmp(Node a, Node b) {
	return (a.next_available_step_count < b.next_available_step_count);
}

//从起始点开始向下深搜,如果能遍历整个棋盘则返回true,否则返回false
bool dfs(int x, int y, int step) {
	vector<Node> v;                    //存储下一步可达节点的vector
	visit[x*8+y] = 1;                  //将当前位置visit设为1,表示该位置已经走过了
	route[step] = x*8+y+1;             //在路径中存储当前位置
	if (step == 63) return true;       //如果遍历完所有格子,返回true

	for (int i = 0; i < 8; i++) {
		int X = x+dir[i][0];
		int Y = y+dir[i][1];
		if (!out_of_map(X, Y) && !visit[X*8+Y]) {
			v.push_back(Node(X,Y));
		}
	}
	//按照nasc值排序,保证优先寻找下一步的nasc小的节点,提高搜索效率
	sort(v.begin(), v.end(), cmp);

	for (int i = 0; i < v.size(); i++) {
		if (dfs(v[i].x, v[i].y, step+1))
			return true;
	}
    //回溯,将访问过的节点的visit值重新置为0
	visit[x*8+y] = 0;
	return false;
}

int main() {
	int T;
	while (1) {
		cin >> T;
		memset(visit, 0, sizeof(visit));
		if (T == -1) break;
		int x = (T-1)/8, y = (T-1)%8;
		if (dfs(x, y, 0)) {
			for (int i = 0; i < 63; i++) {
				cout << route[i] << " ";
			}
			cout << route[63] << endl;
		}
	}
}

