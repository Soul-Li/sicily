#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>

/*
 * 判断线段是否相交
 * T条线段,如果相交则合并,问最后剩下几条线段
 *
 * 构造表示线段的结构体（起点,终点,是否有斜率,斜率的值以及在y轴上的截距）
 *
 * 将T条线段排序,具体排序规则见cmp()函数
 */

using namespace std;

bool equal(double a, double b) {
	if (fabs(a-b) < 1e-8) return true;
	else return false;
}

struct Segment {
	double x1,y1,x2,y2;
	bool has_k;
	double k, y0;
	Segment() {}
	Segment(double _x1, double _y1, double _x2, double _y2) {
		x1 = _x1, y1 = _y1, x2 = _x2, y2 = _y2;
		has_k = true;
		k = y0 = 0;
		if (_x2 < _x1) {
			x1 = _x2, y1 = _y2, x2 = _x1, y2 = _y1;
		} else if(equal(_x1, _x2)) {
			if (_y2 < _y1) {
				y1 = _y2, y2 = _y1;
			}
			has_k = false;
		}
		if (has_k) {
			k = (y2 - y1)/(x2 - x1);
			y0 = y1-k*x1;
		}
	}
};

bool cmp(const Segment s1, const Segment s2) {
	//若均无斜率,则先按x排序,若x都相同则按y排序
	if (!s1.has_k && !s2.has_k)
		return (!equal(s1.x1, s2.x1) ? (s1.x1 < s2.x1) : (s1.y1 < s2.y1));
	//有斜率的总排在没有斜率的前面
	if (!s1.has_k) return false;
	if (!s2.has_k) return true;
	//均有斜率,斜率小的排在前面,相等则截距小的排在前面,截距相同的则x小的排在前面
	if (s1.has_k && s2.has_k) {
		return (!equal(s1.k, s2.k) ? (s1.k < s2.k) : (!equal(s1.y0, s2.y0) ? (s1.y0 < s2.y0) : (s1.x1 < s2.x1)));
	}
}

int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int T;
	Segment seg[10010];
	while (scanf("%d", &T) && T != 0) {
		double a, b, c, d;
		for (int i = 0; i < T; i++) {
			scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
			seg[i] = Segment(a, b, c, d);
		}
		sort(seg, seg+T, cmp);
		//for (int i = 0; i < T; i++) {
		//	printf("%d %lf %lf %lf %lf\n", i, seg[i].x1, seg[i].y1, seg[i].x2, seg[i].y2);
		//}
		int n = T;
		//合并线段
		for (int i = 1; i < T; i++) {
			if (!seg[i-1].has_k && !seg[i].has_k && equal(seg[i-1].x1, seg[i].x1)) {
				//均无斜率且x值相同,若前面一条的终点的y大于等于后面一条起点的y,则表示可以合并
				if (seg[i-1].y2 > seg[i].y1 || equal(seg[i].y1, seg[i-1].y2)) {
					//更新后面一条的终点(看两条线终点的y谁更大),画个图很好理解
					seg[i].y2 = max(seg[i-1].y2, seg[i].y2);
					n--;
				}
			} else if (!seg[i-1].has_k || !seg[i].has_k) continue;
			//斜率相等且截距也相同
			else if (equal(seg[i-1].k,seg[i].k) && equal(seg[i-1].y0, seg[i].y0)) {
				//若前面一条的终点的x大于等于后面一条起点的x,则表示可以合并
				if (seg[i-1].x2 > seg[i].x1 || equal(seg[i-1].x2, seg[i].x1)) {
					//更新后面一条终点的坐标(看两条线段终点的x谁更大)
					seg[i].x2 = max(seg[i-1].x2, seg[i].x2);
					n--;
				}
			}
		}
		printf("%d\n", n);
	}
}

