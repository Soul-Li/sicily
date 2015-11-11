#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>

/*
 * �ж��߶��Ƿ��ཻ
 * T���߶�,����ཻ��ϲ�,�����ʣ�¼����߶�
 *
 * �����ʾ�߶εĽṹ�壨���,�յ�,�Ƿ���б��,б�ʵ�ֵ�Լ���y���ϵĽؾࣩ
 *
 * ��T���߶�����,������������cmp()����
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
	//������б��,���Ȱ�x����,��x����ͬ��y����
	if (!s1.has_k && !s2.has_k)
		return (!equal(s1.x1, s2.x1) ? (s1.x1 < s2.x1) : (s1.y1 < s2.y1));
	//��б�ʵ�������û��б�ʵ�ǰ��
	if (!s1.has_k) return false;
	if (!s2.has_k) return true;
	//����б��,б��С������ǰ��,�����ؾ�С������ǰ��,�ؾ���ͬ����xС������ǰ��
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
		//�ϲ��߶�
		for (int i = 1; i < T; i++) {
			if (!seg[i-1].has_k && !seg[i].has_k && equal(seg[i-1].x1, seg[i].x1)) {
				//����б����xֵ��ͬ,��ǰ��һ�����յ��y���ڵ��ں���һ������y,���ʾ���Ժϲ�
				if (seg[i-1].y2 > seg[i].y1 || equal(seg[i].y1, seg[i-1].y2)) {
					//���º���һ�����յ�(���������յ��y˭����),����ͼ�ܺ����
					seg[i].y2 = max(seg[i-1].y2, seg[i].y2);
					n--;
				}
			} else if (!seg[i-1].has_k || !seg[i].has_k) continue;
			//б������ҽؾ�Ҳ��ͬ
			else if (equal(seg[i-1].k,seg[i].k) && equal(seg[i-1].y0, seg[i].y0)) {
				//��ǰ��һ�����յ��x���ڵ��ں���һ������x,���ʾ���Ժϲ�
				if (seg[i-1].x2 > seg[i].x1 || equal(seg[i-1].x2, seg[i].x1)) {
					//���º���һ���յ������(�������߶��յ��x˭����)
					seg[i].x2 = max(seg[i-1].x2, seg[i].x2);
					n--;
				}
			}
		}
		printf("%d\n", n);
	}
}

