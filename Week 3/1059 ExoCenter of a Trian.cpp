#include<iostream>
#include<cstdio>
#include<cmath>

using namespace std;

//�����Ƴ�O�Ǧ�ABC�Ĵ���
//������ת,��D,G,F,H�ĵ㼴��,��D,G�е�L,��FH�е�N,����LA��NC���㼴��(�������)

#define PI 3.14159265358
#define eps 1e-6
#define INF 1e+15

//��
struct Point {
	double x,y;
	Point() {}
	Point(double _x, double _y):x(_x),y(_y) {};
	Point operator +(const Point& p) {
		Point temp;
		temp.x = x+p.x;
		temp.y = y+p.y;
		return temp;
	}
	Point operator -(const Point& p) {
		Point temp;
		temp.x = x-p.x;
		temp.y = y-p.y;
		return temp;
	}
};

//������ת,����sin(a+b)��cos(a+b)չ�����Ƴ�˳ʱ�����ʱ����ת�Ĺ�ʽ
Point rotate(const Point& p, double angle) {
	Point temp;
	temp.x = p.x*cos(angle)-p.y*sin(angle);
	temp.y = p.x*sin(angle)+p.y*cos(angle);
	return temp;
}

//�������е�
Point middle(const Point& p1, const Point& p2) {
	Point temp;
	temp.x = (p1.x+p2.x)/2.0;
	temp.y = (p1.y+p2.y)/2.0;
	return temp;
}

//ֱ��
struct Line {
	double k,b;
	Line() {}
	Line(const Point& s, const Point& e) {
		if (fabs(e.x-s.x) < eps) {
			k = INF;
			b = s.x;
		} else {
			k = (e.y-s.y)/(e.x-s.x);
			b = e.y-k*e.x;
		}
	}
};

//��ֱ�߽���
Point intersection(const Line& l1, const Line& l2) {
	Point o;
	if (l1.k == INF) {
		o.x = l1.b;
		o.y = l2.k*o.x+l2.b;
	} else if (l2.k == INF) {
		o.x = l2.b;
		o.y = l1.k*o.x+l1.b;
	} else {
		o.x = (l2.b-l1.b)/(l1.k-l2.k);
		o.y = l1.k*o.x+l1.b;
	}
	return o;
}

int main() {
	int n;
	//printf("%f", sin(PI/2));
	scanf("%d", &n);
	Point A,B,C;
	while (n--) {
		scanf("%lf %lf", &A.x, &A.y);
		scanf("%lf %lf", &B.x, &B.y);
		scanf("%lf %lf", &C.x, &C.y);

		Point D,G,L, F,H,N, O;
		//B-A��ʾ��A->B������,����ͼʾ����������ת���Լ��������Ȧ���е������
		D = rotate(B-A, PI/2)+A;
		G = rotate(C-A, -PI/2)+A;
		L = middle(D, G);

		F = rotate(A-C, PI/2)+C;
		H = rotate(B-C, -PI/2)+C;
		N = middle(F, H);

		//����3��ֱ����ѡ2���󽻵�
		O = intersection( Line(L,A), Line(N, C));

		//O.x��O.y�ǳ�Сʱ�п������-0.0,������������
		O.x = fabs(O.x) < eps ? 0: O.x;
		O.y = fabs(O.y) < eps ? 0: O.y;

		printf("%.4lf %.4lf\n", O.x, O.y);
	}
	return 0;
}
