/*
 * main.cpp
 *
 *  Created on: 2014年5月17日
 *      Author: ABCD
 */
#include<iostream>
#include<string>
#include<map>
using namespace std;
//存储姓名和id的结构体
struct name_id {
	string name;
	string id;
};
int main() {
	int n;
	string s1, s2;
	name_id ni[20];
	while (1) {
		cin>> n;
		map<string, string> match;
		map<string, string>::iterator iter;
		if (!n) {
			break;
		} else {
			for (int i = 0; i < n; i++) {
				cin >> s1 >> s2;
				ni[i].name = s1;
				ni[i].id = s2;
			}
			//寻找匹配的id,将匹配到的两个姓名分别放入match中,注意第一个值需要为真正id而非majia
			for (int i = 0; i < n; i++) {
				for (int j = i+1; j < n; j++) {
					if (ni[i].id == ni[j].id) {
						match.insert(make_pair(ni[i].name, ni[j].name));
						                     //  真正id        majia
						break;
					}
				}
			}
			for (iter = match.begin(); iter != match.end(); iter++) {
				cout << (*iter).second << " is the MaJia of " << (*iter).first << endl;
			}
			//题目要求每个case间隔一个\n
			cout << endl;
		}
	}
	return 0;
}
