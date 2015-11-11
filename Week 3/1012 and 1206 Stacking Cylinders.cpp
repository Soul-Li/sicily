#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstdio>

/*
 * ��Ŀ����:��֪ÿ��Բ�İ뾶Ϊ1,����n�����������ײ�����Բ��Բ������,����ѵ���������߲�Բ��Բ������
 *
 * ���㼸����,�ؼ���һ�㻯ģ��,���������һ�㻯2��Բ��Բ�����������2Բͬʱ���е��ϲ�Բ��Բ������ı�ʾ
 *                   /|\
 *                  / |  \  2
 *                 /  |    \
 *                /   |      \
 *           2   /    |      s|(x2,y2)
 *              /     |   s   |            tan(a1) =(y2-y1)/(x2-x1)    (s��ױߵļн�)
 *             /      |s      |            cos(a2) =(s/2) / 2;         (б���������ļн�)
 *            /    s  |       |            a = a1+a2                   (������ױߵļн�)
 *    (x1,y1)/s_______|_______|
 *                                      ������ tempx = x1+2*cos(a)
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
	//1012��1206ֻ�����������ʽ��ͬ
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
		//����������п���û�ź���
		sort(C, C+N, cmp);
		//����Ҫ����N-1�β��ܵõ������Բ������
		for (int i = N-1; i > 0; i--) {
			for (int j = 0; j < i; j++) {
				//б��, �н�a1, �н�a2, �н�a, �ϲ�Բ������
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
