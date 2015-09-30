/*
 * 1093 Air Express.cpp
 *
 *  Created on: 2015年9月29日
 *      Author: ABCD
 */
#include<iostream>
#include<cstdio>
/*
 * 解题思路:
 * 当weight位于某个区间时,我们只需要考虑在它所在区间之上的其他重量区间的最小的pay是否小于当前pay.
 * 例如:
 *   0<weight<w1时,我们只需要考虑(w1,w2]、(w2,w3]、(w3,1000]这三个区间的最小值,即w1+1,w2+1和w3+1所对应的pay是否小于原来的pay
 *   以此类推,可以推出weight位于其他3个区间时的情况
 *   而w1+1,w2+1,w3+1所对应的pay是固定可求的,这里用一个l[0]~l[2]数组来存储
 */
using namespace std;
int main() {
	int w[3],r[4],l[3];
	int T = 1;

	while (scanf("%d %d %d %d %d %d %d", &w[0], &r[0], &w[1], &r[1], &w[2], &r[2], &r[3]) != EOF) {
		cout << "Set number " << T++ << ":" << endl;
		//求出w1+1,w2+1,w3+1所对应的pay值
		l[0] = (w[0]+1)*r[1], l[1] = (w[1]+1)*r[2], l[2] = (w[2]+1)*r[3];
		//  最终重量, 最终支付, 添加重量
		int weight, pay, added = 0;
		while (scanf("%d", &weight) && weight != 0) {
			if(weight < 0 || weight > 1000) break;
			//因为weight值有可能改变,但最后需要原weight值,这里用temp暂存
			int temp = weight;
			//分4种情况讨论,(0, w1],(w1,w2],(w2,w3],(w3,1000)
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



