#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<cstdio>

/*
 * ��Ŀ����:����һ����˾��ĳ��Ա��,�����һ��Ա����нˮ������,�������Ҳ������,��ô���������boss,��������subordinate
 *       �����immediate boss�������boss��нˮ��͵��Ǹ�.
 * n������,ÿ�����Ը���m��Ա����Ϣ��q����ѯ,����ÿ����ѯ��Ա��id,��������immediate boss(���û��,���0)������subordinate����
 *
 * ����˼·:��нˮ�ߵ͸�m��Ա������,���ﰴ��������
 *       ����person����,�ҳ�����immediate boss,��Ӧ���������ҵ���boss��sub�С�
 *       ��нˮ�ӵ͵��ߵ�˳��ͳ�Ƹ���Ա����subordinate����
 *       ��ÿ����ѯ�����ǰ����Ľ��
 */

using namespace std;

struct person {
	int id, salary, height;
	int boss;                //id of immediate boss
	int all_sub = 0;         //sum of subordinate
	vector<int> sub;         //�������ֱ��sub,����ͳ��sub����
};

bool cmp(const person p1, const person p2) {
	return p1.salary < p2.salary;
}


int main() {
	person p[30001];
	int n, m, q;
	scanf("%d", &n);
	while (n--) {
		scanf("%d %d", &m, &q);
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &p[i].id, &p[i].salary, &p[i].height);
			p[i].sub.clear();
			p[i].all_sub = 0;
		}
		sort(p, p+m, cmp);
		int i, j;
		for (i = 0; i < m; i++) {
			//find immediate boss
			for (j = i+1; j < m; j++) {
				if (p[j].height >= p[i].height) break;
			}
			if (j != m) {
				p[i].boss = j;
				p[j].sub.push_back(i);
			} else {
				p[i].boss = -1;
			}
		}
		//count the sum of one person's subordinate
		//������Ҫע��Ҫ��ͳ��salary�͵�all_sub,��ͳ��salary�ߵ�all_sub(�൱���ȼ�������Ҷ�ڵ�,�����Ǹ��ڵ�)
		for (int i = 0; i < m; i++) {
			if (!p[i].sub.empty()) {
				for (int j = 0; j < p[i].sub.size(); j++) {
					p[i].all_sub += p[p[i].sub.at(j)].all_sub + 1;
				}
			}
		}

		while (q--) {
			int temp, index;
			cin >> temp;
			for (index = 0; index < m; index++) {
				if (p[index].id == temp) break;
			}
			if (p[index].boss != -1) {
				cout << p[p[index].boss].id << " " << p[index].all_sub << endl;
			} else {
				cout << "0 " << p[index].all_sub << endl;
			}
		}
	}
}

