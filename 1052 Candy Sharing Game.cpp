#include<iostream>
#include<cstdio>

using namespace std;

/*
 * ģ�������,������Ŀ������
 * N������,ÿ����ʦ��һ������,ÿ�����Ӷ��ѵ�ǰ�Լ����ǹ���һ��ָ����ֱߵĺ���
 * �����,������ӵ��ǹ���Ϊ����,��ô��ʦ�������һ���ǹ�ʹ���ǹ������ż��,Ȼ���ٴ�����
 * ��Ϸ������������ÿ�����ӵ��ǹ�����ͬ,�����Ϸ����ʱ��ʦ�����ӵĴ����ͺ������յ��ǹ���
 *
 * ��Ŀ�б�ע:��Ϸ��һ���������
 * Notes:
 * The game ends in a finite number of steps because:
 * 1. The maximum candy count can never increase.
 * 2. The minimum candy count can never decrease.
 * 3. No one with more than the minimum amount will ever decrease to the minimum.
 * 4. If the maximum and minimum candy count are not the same, at least one student with the minimum amount must have their count increase
 */

//���ÿ�����ӵ��ǹ����Ƿ�Ϊż��
bool check_equal(int A[], int n) {
	int standard = A[0];
	for (int i = 1; i < n; i++) {
		if (A[i] != standard) return false;
	}
	return true;
}

//ģ�ⴵ���ӵĹ���
void blow(int A[], int n) {
	int temp[n];
	for (int i = 0; i < n; i++) {
		temp[i] = A[i]/2;
		A[i] = temp[i];
	}
	for (int i = 0; i < n; i++) {
		if (i == 0) A[i] += temp[n-1];
		else A[i] += temp[i-1];
	}
}

//ģ����ʦ���ǹ�
void if_odd(int A[], int n) {
	for (int i = 0; i < n; i++) {
		if (A[i] % 2 == 0) continue;
		A[i]++;
	}
}

int main() {
	int N;
	int Student[10000];
	while( cin >> N && N != 0) {
		int time = 0;
		bool equal = false;
		for (int i = 0; i < N; i++) {
			cin >> Student[i];
		}
		while (1) {
			equal = check_equal(Student, N);
			if (equal) break;
			blow(Student, N);
			if_odd(Student, N);
			time++;
		}
		cout << time << " " << Student[0] << endl;
	}
}
