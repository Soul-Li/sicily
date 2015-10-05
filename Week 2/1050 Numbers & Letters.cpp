#include<iostream>
#include<cstdio>

using namespace std;
/*
 * ����24�����Ϸ,5��������������5��)ͨ��һЩ����(+ - * /),���ܷ�õ�Ŀ����,���ܵĻ�������Եõ���С��target����������
 *
 * �ⷨ:����
 *     �ӵ�ǰ�����������ȡ2�����п��ܵ���������(ע��������ܲ���С�����ܳ�0�Լ�������2�����)
 *     �տ�ʼ�Ҳ��õ���vector,�������ֲ�������,iter�����������鷳
 *     ��������ṹ,���ǿ��Խ���ǰҪ�����2����������1���õ�n-1λ����������,����1�������洢������,Ȼ����n-1���ȵ������������
 *
 */

#define inf -99999999;

int target;
int approach = inf;          //�����п����и����Ľ������,����approach���ܳ�ʼ��Ϊ0
int M[5];

//��������,approach���ܳ���target
void cal_approach(int n) {
	for (int i = 0; i < n; i++) {
		if (M[i] <= target && M[i] > approach)
			approach = M[i];
	}
}

void do_arithmetic(int n) {
	cal_approach(n);
	if (approach == target) return;
	if (n == 1) return;
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			int temp1 = M[i], temp2 = M[j];
			M[j] = M[n-1];

			M[i] = temp1+temp2;
			do_arithmetic(n-1);
			M[i] = temp1-temp2;
			do_arithmetic(n-1);
			M[i] = temp2-temp1;
			do_arithmetic(n-1);
			M[i] = temp1*temp2;
			do_arithmetic(n-1);
			if (temp2 != 0 && (temp1 % temp2 ==0)) {
				M[i] = temp1/temp2;
				do_arithmetic(n-1);
			}
			if (temp1 != 0 && (temp2 % temp1 ==0)) {
				M[i] = temp2/temp1;
				do_arithmetic(n-1);
			}
			//һ���������,����,������һ��forѭ��
			M[i] = temp1, M[j] = temp2;
		}
	}
}

int main() {
	int N;
	cin >> N;
	while (N--) {
		cin >> M[0] >> M[1] >> M[2] >> M[3] >> M[4] >> target;
		approach = inf;
		do_arithmetic(5);
		cout << approach << endl;
	}
}
