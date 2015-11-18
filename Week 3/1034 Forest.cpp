#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

vector<int> vertex[105];           //���㼯��
int in[105], width[105];           //��������, width[i]��ʾ���Ϊiʱ�Ŀ��
bool visited[105], circle;         //�Ƿ񱻷���, �Ƿ���ڻ�
int Width, Depth;                  //���Ŀ��, �������

//DFS
void next_level(int u, int d) {
	//����Ƿ��л�����
	if (visited[u]) {
		circle = true;
		return;
	}
	visited[u] = true;
	//ʵʱ����������
	if (d > Depth) Depth = d;
	//���µ�ǰ��ȵĿ��
	width[d]++;
	//ʵʱ���������
	if (width[d] > Width) Width = width[d];

	for (int i = 0; i < vertex[u].size(); i++) {
		//����������һ���ӽڵ�,���+1
		next_level(vertex[u].at(i), d+1);
	}
}

int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) && n != 0) {
		Width = 0, Depth = 0;
		circle = false;
		//�ڵ���==����,�ش��ڻ�
		if (m >= n) {
			circle = true;
		}
		//initialize
		for (int i = 0; i < 105; i++) {
			vertex[i].clear();
			in[i] = 0;
			width[i] = 0;
			visited[i] = false;
		}
		int u, v;
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &u, &v);
			vertex[u].push_back(v);
			in[v]++;
		}
		//�����Ϊ0�ĵ��������
		for (int i = 1; i <= n; i++) {
			if (in[i] == 0) {
				next_level(i, 0);
			}
		}
		//���һ��������,������δ���ʹ���,֤�������Ի�
		for (int i = 1; i <= n; i++) {
			if (!visited[i]) circle = true;
		}
		if (circle) cout << "INVALID\n";
		else cout << Depth << " " << Width << endl;
	}
}
