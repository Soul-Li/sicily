#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
/*
 * �Ż�����,�������ۺ���nasc()���Ľ���������,��֤ÿ���ҵ���һ�����ǵ�ǰ��Ӧ��ȥ�����ĵ�
 */


using namespace std;

//�������ߵ�8������Ķ�ά����,��(x-2,y-1)˳ʱ��ֱ��(x-2,y+1)
int dir[8][2] = {-2,-1, -1,-2, 1,-2, 2,-1, 2,1, 1,2, -1,2, -2,1};
//�ж������ϵĸ����Ƿ��߹�
bool visit[64];
//�洢���ߵ�·��
int route[64];

//�ж����Ƿ�����������
bool out_of_map(int x, int y) {
	if (x < 0 || x > 7 || y < 0 || y > 7) return true;
	return false;
}

//���㵱ǰ������λ������һ���ĺϷ�λ�õ�����
int nasc(int x, int y) {
	int count = 0;
	for (int i = 0; i < 8; i++) {
		int X = x+dir[i][0];
		int Y = y+dir[i][1];
		if (!out_of_map(X, Y) && !visit[X*8+Y]) count++;
	}
	return count;
}

//x,y����ǰ����,next_available_step_count������һ�����ߵĺϷ�λ������
struct Node {
	int x;
	int y;
	int next_available_step_count;
	Node(int X, int Y) {
		x = X;
		y = Y;
		next_available_step_count = nasc(X, Y);
	}
};

//������,����ÿ���ڵ����һ���Ϸ���Ŀ�ӵ͵�������
bool cmp(Node a, Node b) {
	return (a.next_available_step_count < b.next_available_step_count);
}

//����ʼ�㿪ʼ��������,����ܱ������������򷵻�true,���򷵻�false
bool dfs(int x, int y, int step) {
	vector<Node> v;                    //�洢��һ���ɴ�ڵ��vector
	visit[x*8+y] = 1;                  //����ǰλ��visit��Ϊ1,��ʾ��λ���Ѿ��߹���
	route[step] = x*8+y+1;             //��·���д洢��ǰλ��
	if (step == 63) return true;       //������������и���,����true

	for (int i = 0; i < 8; i++) {
		int X = x+dir[i][0];
		int Y = y+dir[i][1];
		if (!out_of_map(X, Y) && !visit[X*8+Y]) {
			v.push_back(Node(X,Y));
		}
	}
	//����nascֵ����,��֤����Ѱ����һ����nascС�Ľڵ�,�������Ч��
	sort(v.begin(), v.end(), cmp);

	for (int i = 0; i < v.size(); i++) {
		if (dfs(v[i].x, v[i].y, step+1))
			return true;
	}
    //����,�����ʹ��Ľڵ��visitֵ������Ϊ0
	visit[x*8+y] = 0;
	return false;
}

int main() {
	int T;
	while (1) {
		cin >> T;
		memset(visit, 0, sizeof(visit));
		if (T == -1) break;
		int x = (T-1)/8, y = (T-1)%8;
		if (dfs(x, y, 0)) {
			for (int i = 0; i < 63; i++) {
				cout << route[i] << " ";
			}
			cout << route[63] << endl;
		}
	}
}

