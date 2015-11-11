/*
 * 1093 Air Express.cpp
 *
 *  Created on: 2015��9��29��
 *      Author: ABCD
 */
#include<iostream>
#include<cstdio>
/*
 * ����˼·:
 * ��weightλ��ĳ������ʱ,����ֻ��Ҫ����������������֮�ϵ����������������С��pay�Ƿ�С�ڵ�ǰpay.
 * ����:
 *   0<weight<w1ʱ,����ֻ��Ҫ����(w1,w2]��(w2,w3]��(w3,1000]�������������Сֵ,��w1+1,w2+1��w3+1����Ӧ��pay�Ƿ�С��ԭ����pay
 *   �Դ�����,�����Ƴ�weightλ������3������ʱ�����
 *   ��w1+1,w2+1,w3+1����Ӧ��pay�ǹ̶������,������һ��l[0]~l[2]�������洢
 */
using namespace std;
int main() {
	int w[3],r[4],l[3];
	int T = 1;

	while (scanf("%d %d %d %d %d %d %d", &w[0], &r[0], &w[1], &r[1], &w[2], &r[2], &r[3]) != EOF) {
		cout << "Set number " << T++ << ":" << endl;
		//���w1+1,w2+1,w3+1����Ӧ��payֵ
		l[0] = (w[0]+1)*r[1], l[1] = (w[1]+1)*r[2], l[2] = (w[2]+1)*r[3];
		//  ��������, ����֧��, �������
		int weight, pay, added = 0;
		while (scanf("%d", &weight) && weight != 0) {
			if(weight < 0 || weight > 1000) break;
			//��Ϊweightֵ�п��ܸı�,�������Ҫԭweightֵ,������temp�ݴ�
			int temp = weight;
			//��4���������,(0, w1],(w1,w2],(w2,w3],(w3,1000)
			if (0 < weight && weight <= w[0]) {
				pay = weight*r[0];
				for (int i = 0; i < 3; i++) {
					if (l[i] < pay && (w[i]+1) > weight) {
						pay = l[i];
						weight = w[i]+1;
					}
				}
			} else if (w[0] < weight && weight <= w[1]) {
				pay = weight*r[1];
				for (int i = 1; i < 3; i++) {
					if (l[i] < pay && (w[i]+1) > weight) {
						pay = l[i];
						weight = w[i]+1;
					}
				}
			} else if (w[1] < weight && weight <= w[2]) {
				pay = weight*r[2];
				for (int i = 2; i < 3; i++) {
					if (l[i] < pay && (w[i]+1) > weight) {
						pay = l[i];
						weight = w[i]+1;
					}
				}
			} else {
				pay = weight*r[3];
			}
			added = weight - temp;
			cout << "Weight (" << temp << ") has best price $" << pay << " (add " << added << " pounds)" << endl;
		}
		cout << endl;
	}
}



