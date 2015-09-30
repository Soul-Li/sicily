#include<iostream>
#include<cstring>
using namespace std;

/*
 * ����˼·:��̬�滮
 * ��ΪP1��ȡ�Ʒ�ʽֻ��2��,��߻����ұ�,��P2����Ϊ��֪,ʣ��������ı����ִ�ȡ�ı�,��ͬ��ȡ��ߵ�.
 * ����״̬ת�Ʒ���:
 *                       ��ߡ�>=���ұߡ����������������ұߡ��������
 * �����:
 *     begin~end  ---> (begin+2,end)   or (begin+1,end-1)
 * ���ұ�:
 *     begin~end  ---> (begin+1,end-1) or (begin, end-2)
 * ��������:
 *     end-begin = 2, ��ʱֱ��ȡ�����нϴ��������
 */

int cards[1001];
int maxSum[1001][1001];
int choose(int begin, int end) {
	if (begin > end) return 0;

	if (maxSum[begin][end] != -1)
		return maxSum[begin][end];

	if (begin+1 == end) {
		maxSum[begin][end] = ((cards[begin] > cards[end]) ? cards[begin] : cards[end]);
		return maxSum[begin][end];
	}

	int chleft = 0;
	//ȡ��ߵ�һ��,��cards[begin]          ģ��P2ѡ��,����2>��1,����������Ϊ��3����1������Ϊ��2����2
	chleft = chleft + cards[begin] + ((cards[begin+1] >= cards[end]) ? choose(begin+2, end) : choose(begin+1, end-1));

	int chright = 0;
	//����֮��:
	//chright = chright + cards[end] + ((cards[end-1] >= cards[begin]) ? choose(begin, end-2) : choose(begin+1, end-1));
	//��Ϊ���������ʱ,P2��̰���㷨Ĭ��ȡ��ߣ�������ȷд������:
	chright = chright + cards[end] + ((cards[begin] >= cards[end-1]) ? choose(begin+1, end-1) : choose(begin, end-2));

	maxSum[begin][end] = (chleft > chright) ? chleft : chright;
	return maxSum[begin][end];
}

int main() {
	int n, t = 1;
	while (cin >> n && n) {
		int sum = 0;
		memset(maxSum, -1, sizeof(maxSum));
		for (int i = 0; i < n; i++) {
			cin >> cards[i];
			sum += cards[i];
		}
		int p1 = choose(0, n-1);
		int p2 = sum-p1;
		cout << "In game " << t << ", the greedy strategy might lose by as many as ";
		cout << ((p1>p2)?(p1-p2):(p2-p1)) << " points." << endl;
		t++;
	}
}
