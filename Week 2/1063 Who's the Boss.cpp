#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<cstdio>

/*
 * 题目大意:对于一个公司的某个员工,如果另一个员工的薪水高于你,而且身高也高于你,那么他就是你的boss,你是他的subordinate
 *       而你的immediate boss则是你的boss中薪水最低的那个.
 * n个测试,每个测试给定m个员工信息和q个查询,对于每个查询的员工id,给出他的immediate boss(如果没有,输出0)和他的subordinate数量
 *
 * 解题思路:按薪水高低给m个员工排序,这里按升序排列
 *       遍历person数组,找出他的immediate boss,对应把他存入找到的boss的sub中。
 *       按薪水从低到高的顺序统计各个员工的subordinate总数
 *       对每个查询输出当前计算的结果
 */

using namespace std;

struct person {
	int id, salary, height;
	int boss;                //id of immediate boss
	int all_sub = 0;         //sum of subordinate
	vector<int> sub;         //存放所有直接sub,方便统计sub总数
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
		//这里需要注意要先统计salary低的all_sub,再统计salary高的all_sub(相当于先计算树的叶节点,最后才是根节点)
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

