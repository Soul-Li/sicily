#include<iostream>
#include<string>
#include<map>
#include<algorithm>
using namespace std;

/*
 * 简单题,注意friend list 大小写不区分,此处有可能在sender list设为小写挖坑
 * 所以在插入map前需要全部转换为小写或大写
 * 剩下的就是简单的查找
 * 为避免重复计数,设置map的第二个参数为int表示查找到的次数
 * 只有当找到name且次数为0时即第一次查到count++
 * 最后用总人数减去count即得结果
 */

string toLowerCase(string& s) {
	for (int i = 0; i < s.length(); i++) {
		if (s[i] >= 'A' && s[i] <= 'Z') s[i] += 32;
	}
	return s;
}


int main() {
	int n, m, count = 0;
	string name;
	map<string, int> friends;
	map<string, int>::iterator iter;
	while (cin >> n && n) {
		cin >> m;
		count = 0;
		for (int i = 0; i < n; i++) {
			cin >> name;
			friends.insert(make_pair(toLowerCase(name), 0));
		}
		for (int i = 0; i < m; i++) {
			cin >> name;
			iter = friends.find(toLowerCase(name));
			//iter不能为end,因为有些sender是不在friend list中的
			if (iter != friends.end() && (*iter).second == 0) {
				count++;
				//避免查找到重复姓名
				(*iter).second++;
			}
		}
		cout << n-count << endl;
		//细节问题
		friends.clear();
	}
}
