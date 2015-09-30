#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
/*
 * @first �������
 * @last �����յ�
 * @average ƽ����
 */
struct quarter {
	int first;
	int last;
	double average;
	quarter(int f, int l, double a) {
		first = f;
		last = l;
		average = a;
	}
};
//sort����,�˴�����������,����q1>q2�践��true;
bool cmp(const quarter& q1, const quarter& q2) {
	if (q1.average > q2.average) return true;
	if (q1.average == q2.average) {
		if ((q1.last-q1.first) > (q2.last-q2.first)) return true;
		if ((q1.last-q1.first) == (q2.last-q2.first)) {
			if (q1.first < q2.first) return true;
		}
	}
	return false;
}

int main() {
	int N, n;
	cin >> N;
	n = N;
	while (N--) {
		vector<int> Quarters;
		vector<quarter> A;
		int NofQ, NofR, NofM;
		cin >> NofQ >> NofR >> NofM;
		for (int i = 0; i < NofQ; i++) {
			int num;
			cin >> num;
			Quarters.push_back(num);
		}
		//����ÿ���������������䣬������A��
		for (int from = 0; from < Quarters.size(); from++) {
			for (int end = from+NofM-1; end < Quarters.size(); end++) {
				int sum = 0;
				for (int i = from; i <= end; i++) {
					sum += Quarters[i];
				}
				A.push_back(quarter(from+1, end+1, (double)sum/(end-from+1)));
			}
		}
		//����ĿҪ��������
		sort(A.begin(), A.end(), cmp);
		cout << "Result for run " << (n-N) << ":" << endl;
		for (int i = 0; i < NofR && i < A.size(); i++) {
			cout << A[i].first << "-" << A[i].last << endl;
		}
	}
}
