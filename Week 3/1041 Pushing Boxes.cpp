#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>

/*
 * 有四面可以移动的墙,墙里面有很多箱子,墙会推动箱子,推不动的时候墙就不移动了
 * 给你大小为N*M的格子图,n个箱子,接下来是墙的移动(用up,right,down,left)+m(偏移)表示
 * 问你最后那n个箱子所处的位置
 *
 * 模拟推箱子的过程
 * 为了简化每次推的过程(不是一步一步推，那不是很愚?)我们可以先求出该方向上墙所能移动的最大距离
 * 例如:
 *    求向左或向右能推动的最大距离,我们首先需要知道每一行的箱子数的最大值,通过getMaxBoxNumByRow()获得
 *    真正能移动的最大距离就是_right-_left-getMaxBoxNumByRow()与offset两者的较小值
 *    移动的过程比较巧妙,在程序内会说明
 * 最后,当达到"done"时,我们在按题目给的顺序排列所有的箱子,依次输出它们的位置即可
 */

using namespace std;

struct Box {
	int x, y;
};

int N, M, n;
int _left, _right, _down, _top;
Box box[11];
int RowBoxNum[21];
int ColBoxNum[21];

int getMaxBoxNumByRow() {
	int max = 0;
	for (int i = 0; i < N; i++) {
		if (RowBoxNum[i] > max)
			max = RowBoxNum[i];
	}
	return max;
}

int getMaxBoxNumByCol() {
	int max = 0;
	for (int i = 0; i < M; i++) {
		if (ColBoxNum[i] > max)
			max = ColBoxNum[i];
	}
	return max;
}

//四个方向的移动,箱子移动的先后顺序不同,我们总是优先关注  最靠近要移动的这面墙  的箱子
//我们要求优先考虑的箱子总排在每个新行/列的最前面,这个要求与我们在移动中的处理有关
bool cmpup(const Box& b1, const Box& b2) {
	return (b1.y == b2.y ? b1.x > b2.x : b1.y < b2.y); //x越大月靠近底部
}
bool cmpdown(const Box& b1, const Box& b2) {
	return (b1.y == b2.y ? b1.x < b2.x : b1.y < b2.y); //x越小越靠近顶部
}
bool cmpleft(const Box& b1, const Box& b2) {
	return (b1.x == b2.x ? b1.y > b2.y : b1.x < b2.x); //y越大越靠近右部
}
bool cmpright(const Box& b1, const Box& b2) {
	return (b1.x == b2.x ? b1.y < b2.y : b1.x < b2.x); //y越小越靠近左部
}


void move(string direction, int offset) {
	if (direction == "up") {
		int canOff = _down-_top-getMaxBoxNumByCol()+1;
		int realOff = (canOff < offset ? canOff : offset);
		sort(box, box+n, cmpup);

		//上下移动与y关系不大
		int x, y = -1;
		for (int i = 0; i < n; i++) {
			//这表明box[i]是新列排在最前的箱子,也是最靠近顶部的墙的箱子
			if (box[i].y != y) {
				y = box[i].y;
				//该列箱子能到达的最远位置的x
				x = _down-realOff;
			} else {
				//画个图就明白了,讲不清楚...
				x--;
			}
			//表明该箱子原本的位置肯定会改变(被墙往上推了),到达当前的x的位置
			if (box[i].x > x) {
				RowBoxNum[box[i].x]--;
				box[i].x = x;
				RowBoxNum[box[i].x]++;
			}
		}
	} else if (direction == "down") {
		int canOff = _down-_top-getMaxBoxNumByCol()+1;
		int realOff = (canOff < offset ? canOff : offset);
		sort(box, box+n, cmpdown);
		int x, y = -1;
		//向下移
		for (int i = 0; i < n; i++) {
			if (box[i].y != y) {
				y = box[i].y;
				x = _top+realOff;
			} else {
				x++;
			}

			if (box[i].x < x) {
				RowBoxNum[box[i].x]--;
				box[i].x = x;
				RowBoxNum[box[i].x]++;
			}
		}
	} else if (direction == "left") {
		int canOff = _right-_left-getMaxBoxNumByRow()+1;
		int realOff = (canOff < offset ? canOff : offset);
		sort(box, box+n, cmpleft);
		int x = -1, y;
		//向左移
		for (int i = 0; i < n; i++) {
			if (box[i].x != x) {
				x = box[i].x;
				y = _right-realOff;
			} else {
				y--;
			}

			if (box[i].y > y) {
				ColBoxNum[box[i].y]--;
				box[i].y = y;
				ColBoxNum[box[i].y]++;
			}
		}
	} else if (direction == "right") {
		int canOff = _right-_left-getMaxBoxNumByRow()+1;
		int realOff = (canOff < offset ? canOff : offset);
		sort(box, box+n, cmpright);
		int x = -1, y;
		//向右移
		for (int i = 0; i < n; i++) {
			if (box[i].x != x) {
				x = box[i].x;
				y = _left+realOff;
			} else {
				y++;
			}

			if (box[i].y < y) {
				ColBoxNum[box[i].y]--;
				box[i].y = y;
				ColBoxNum[box[i].y]++;
			}
		}
	}
}
//向下和向右相似,向上和向左相似


int main() {
	//freopen("in.txt", "r", stdin);

	int T= 0;
	while (1) {
		scanf("%d %d", &N, &M);
		if (N == 0 && M == 0) break;
		T++;
		//最大的边界值
		_left = 0, _right = M-1, _top = 0, _down = N-1;


		for (int i = 0; i < N; i++) {
			RowBoxNum[i] = 0;
			for (int j = 0; j < M; j++)
				ColBoxNum[j] = 0;
		}
		memset(box, 0, sizeof(box));
		scanf("%d", &n);

		for (int i = 0; i < n; i++) {
			scanf("%d %d", &box[i].x, &box[i].y);
			RowBoxNum[box[i].x]++;
			ColBoxNum[box[i].y]++;
		}

		while (1) {
			string direction;
			int m;
			cin >> direction;
			if (direction == "done") {
				printf("Data set %d ends with boxes at locations",T);
				sort(box, box+n, cmpright);
				for (int i = 0; i < n; i++) {
					printf(" (%d,%d)", box[i].x, box[i].y);
				}
				printf(".\n");
				break;
			} else {
				scanf("%d", &m);
				move(direction, m);
			}
		}
	}
	return 0;
}
