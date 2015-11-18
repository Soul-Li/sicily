#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>

using namespace std;

/*
 * ���ַ���һԪ���̵ĸ�,Ҳ����ţ�ٵ���
 */

#define eps 1e-6
double Month[13];

double cal_money(int startmonth, int endmonth, double rate) {
	double sum = 0;
	for (int i = startmonth; i <= endmonth; i++) {
		sum += Month[i]*pow(rate, (double)endmonth-i+1);
	}
	return sum;
}

double cal_rate(int endmonth, double money) {
	int startmonth;
	for (int i = 1; i < 13; i++) {
		if (fabs(Month[i]-0.0) > eps) {
			startmonth = i;
			break;
		}
	}
	double R_L = 1.0, R_R = 2.0, Rate = (R_L+R_R)/2.0;
	while (1) {
		if (fabs(money-cal_money(startmonth, endmonth, Rate)) < eps)
			break;
		else if (money > cal_money(startmonth, endmonth, Rate)) {
			R_L = Rate;
			Rate = (R_L+R_R)/2.0;
			continue;
		} else {
			R_R = Rate;
			Rate = (R_L+R_R)/2.0;
			continue;
		}
	}
	return Rate;
}

int main() {
	//freopen("i.in", "r", stdin);
	int N, T = 0;
	while (1) {
		scanf("%d", &N);
		if (N == -1) break;
		T++;
		memset(Month, 0.0, sizeof(Month));
		int month;
		double money;
		//���������п��ܶ��money��Ӧһ��month
		for (int i = 0; i < N; i++) {
			scanf("%d%lf", &month, &money);
			Month[month] += money;
		}
		scanf("%d%lf", &month, &money);
		//ע�������ʽ,��Case����1ʱ��Ҫ�������һ������
		if (T > 1) printf("\n");
		printf("Case %d: %.5lf\n", T, cal_rate(month, money)-1);
	}
	return 0;
}
