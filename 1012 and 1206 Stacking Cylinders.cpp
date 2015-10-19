#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstdio>

/*
 * 题目大意:已知每个圆的半径为1,给定n个坐标代表最底层所有圆的圆心坐标,求出堆叠起来的最高层圆的圆心坐标
 *
 * 计算几何题,关键在一般化模型,在这里就是一般化2个圆的圆心坐标求出与2圆同时相切的上层圆的圆心坐标的表示
 *                   /|\
 *                  / |  \  2
 *                 /  |    \
 *                /   |      \
 *           2   /    |      s|(x2,y2)
 *              /     |   s   |            tan(a1) =(y2-y1)/(x2-x1)    (s与底边的夹角)
 *             /      |s      |            cos(a2) =(s/2) / 2;         (斜边与左腰的夹角)
 *            /    s  |       |            a = a1+a2                   (左腰与底边的夹角)
 *    (x1,y1)/s_______|_______|
 *                                      所以有 tempx = x1+2*cos(a)
 *                                          tempy = y1+2*sin(a)
 */


using namespace std;

struct circle {
	double x;
	double y;
	circle () {}
	circle (double xx, double yy) {
		x = xx;
		y = yy;
	}
};

bool cmp(const circle a, const circle b) {
	return a.x < b.x;
}

int main() {
	//1012与1206只是输入输出格式不同
	int T, time = 0;
	scanf("%d", &T);
	while (T--) {

		int N;
		circle C[11];
		scanf("%d", &N);
		if (N == 0) break;
		time++;

		for (int i = 0; i < N; i++) {
			scanf("%lf", &C[i].x);
			C[i].y = 1;
		}
		//输入的坐标有可能没排好序
		sort(C, C+N, cmp);
		//共需要计算N-1次才能得到顶层的圆心坐标
		for (int i = N-1; i > 0; i--) {
			for (int j = 0; j < i; j++) {
				//斜边, 夹角a1, 夹角a2, 夹角a, 上层圆心坐标
				double s = sqrt((C[j+1].x-C[j].x)*(C[j+1].x-C[j].x) + (C[j+1].y-C[j].y)*(C[j+1].y-C[j].y));
				double a1 = atan((C[j+1].y-C[j].y)/(C[j+1].x-C[j].x));
				double a2 = acos((s/2)/2);
				double a = a1+a2;
				C[j].x = C[j].x+2*cos(a);
				C[j].y = C[j].y+2*sin(a);
			}
		}
		printf("%d: %.4lf %.4lf\n", time, C[0].x, C[0].y);
	}
	return 0;
}
