#include<iostream>
#include<cstring>
#include<cstdio>

using namespace std;

int n, m, d;
bool isPrime[10000];
bool selected[1010];
int answer[1010];
bool finish;
//ɸ��������
void Prime() {
	memset(isPrime, true, sizeof(isPrime));
	isPrime[0] = isPrime[1] = false;
	//Ϊʲô�˴�������i*i<=10000(����һ��ʱ��)? ��Ϊ����ѭ���п��Կ���,��i��Сʱ,j�Ѿ�ȡ��10000/i֮�����Щֵ
	for (int i = 2; i * i <= 10000; i++) {
		if (isPrime[i]) {
			for (int j = 2; j <= 10000/i; j++) {
				isPrime[j*i] = false;
			}
		}
	}
}


//�Ӻ���ǰ��ͱȽϺ���
bool check_sum(int pos, int val) {
	/*
	 * i = pos-1 >= 0��ʾ����pos>=1Ҳ������2������
	 * i >= pos-d+1 ��ͼ��֪,��pos��i���d������
	 * ����:�Ӻ���ǰ���,ÿ��һ������ֻ��Ҫһ��ѭ���㶨
	 * ���ÿ�δ�ǰ�������,���̻�ܸ���
	 */
	for (int i = pos-1; i >= 0 && i >= pos-d+1; i--) {
		val += answer[i];
		if(isPrime[val]) return false;
	}
	return true;
}

void dfs(int pos) {
	for (int i = n; i <= m; i++) {
		if (!selected[i] && check_sum(pos, i)) {
			selected[i] = true;
			answer[pos] = i;
			//��ʾ��������������
			if (pos == m-n) {
				finish = true;
				return;
			}
			//����һλ������
			dfs(pos+1);
			if (finish) return;
			//����,�����������selected��Ϊfalse,����forѭ��
			//���forѭ����ֹ��û������
			//˵����һ����������Ĳ���
			//��ô��������һ����dfs(pos+1)��
			//��˾��������������
			selected[i] = false;
		}
	}
}

int main() {
	Prime();
	while(1) {
		cin >> n >> m >> d;
		if (n == 0 && m == 0 && d == 0) break;
		memset(selected, false, sizeof(selected));
		finish = false;
		dfs(0);
		if (finish) {
			printf("%d", answer[0]);
			for (int i = 1; i <= m-n; i++) {
				printf(",%d", answer[i]);
			}
			printf("\n");
		} else {
			printf("No anti-prime sequence exists.\n");
		}
	}
}
