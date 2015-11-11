#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

/*
 * ����MST,û�п�,ֱ����Kruskal+���鼯�Ϳ�AC
 */

#define MAX 100000

struct edge {
	int from;
	int to;
	int distance;
	edge() {}
	edge(int _from, int _to, int _distance) {
		from = _from, to = _to, distance = _distance;
	}
};

edge E[MAX];
int father[MAX];
int son[MAX];

bool cmp(const edge e1, const edge e2) {
	return e1.distance < e2.distance;
}

//���鼯,�ҵ���ǰ�ڵ�ĸ�
int getFather(int x) {
	return (x == father[x] ? father[x] : getFather(father[x]));
}

bool isSame(int x, int y) {
	return getFather(x) == getFather(y);
}

//�ϲ�������ͬ�ļ���
void merge(int x, int y) {
	while (x != father[x]) x = getFather(father[x]);
	while (y != father[y]) y = getFather(father[y]);
	if (son[x] >= son[y]) {
		son[x] += son[y];
		father[y] = x;
	} else {
		son[y] += son[x];
		father[x] = y;
	}
}

int main() {
	int P, R;
	while (scanf("%d", &P) && P != 0) {
		scanf("%d", &R);
		int num = 0, answer = 0;
		for (int i = 1; i <= R; i++) {
			int f,t,d;
			scanf("%d %d %d", &f, &t, &d);
			E[i] = edge(f, t, d);
			father[i] = i;
			son[i] = 1;
		}
		sort(E+1, E+R+1, cmp);
		for (int i = 1; i <= R; i++) {
			int from = E[i].from, to = E[i].to;
			if (isSame(from, to)) continue;
			merge(from, to);
			num++;
			answer += E[i].distance;
			if (num == P-1) break;
		}
		printf("%d\n", answer);
	}
}
