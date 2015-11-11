#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;
/*
 *
 * 构造棋盘,空格子为0,Queen为1,Knight为2,Pawn为3,safe表示安全的格子数目,首先需要减去上述三种棋子的数目
 *
 * 对每个Queen和Knight分别求它们occupied的方格，并标记为-1
 *
 * 遍历完所有的棋盘格子,最终获得-1的count值即为所求
 */

int Board[1010][1010];
int N, M;
//Q_dir, 皇后的可移动方向
int Q_dir[8][2] = {-1,-1, 0,-1,  1,-1,  1,0, 1, 1, 0,1, -1,1, -1,0};
//K_dir, 马的可移动方向
int K_dir[8][2] = {-2,-1, -2,1, -1,-2, -1,2, 1,-2, 1,2, 2,-1, 2,1};

bool out_of_bound(int i, int j) {
	if (i < 1 || i > N) return true;
	if (j < 1 || j > M) return true;
	return false;
}


void Queen_occupied(int row, int col) {
	for (int i = 0; i < 8; i++) {
		//需要记录下原始位置
		int pos_x = row, pos_y = col;
		pos_x += Q_dir[i][0];
		pos_y += Q_dir[i][1];
		while (!out_of_bound(pos_x, pos_y)) {
			//当前格子既不是Q,K,P
			if (Board[pos_x][pos_y] != 3 && Board[pos_x][pos_y] != 2 && Board[pos_x][pos_y] != 1) {
				Board[pos_x][pos_y] = -1;
			//不能继续前进,退出循环
			} else {
				break;
			}
			pos_x += Q_dir[i][0];
			pos_y += Q_dir[i][1];
		}
	}
}

void Knight_occupied(int row, int col) {
	for (int i = 0; i < 8; i++) {
		int pos_x = row, pos_y = col;
		pos_x += K_dir[i][0];
		pos_y += K_dir[i][1];
		//Knight只能找周围的8个位置
		if (!out_of_bound(pos_x, pos_y)) {
			if (Board[pos_x][pos_y] == 0)
				Board[pos_x][pos_y] = -1;
		}
	}
}

//遍历棋盘
void cal_safe() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (Board[i][j] == 1) {
				Queen_occupied(i, j);
			} else if (Board[i][j] == 2) {
				Knight_occupied(i, j);
			}
		}
	}
}

int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int T = 0;
	while (scanf("%d %d", &N, &M)) {
		if (N == 0 && M == 0) break;
		T++;
		memset(Board, 0, sizeof(Board));
		int k, r, c, count = 0;
		for (int i = 1; i <= 3; i++) {
			scanf("%d", &k);
			for (int j = 1; j <= k; j++) {
				scanf("%d %d", &r, &c);
				Board[r][c] = i;
			}
		}
		cal_safe();
		//获取所有的值为0的格子,表示该处是安全的
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				if (Board[i][j] == 0)
					count++;
			}
		}
		printf("Board %d has %d safe squares.\n", T, count);
	}
}

