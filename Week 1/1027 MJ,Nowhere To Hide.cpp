/*
 * main.cpp
 *
 *  Created on: 2014��5��17��
 *      Author: ABCD
 */
#include<iostream>
#include<string>
#include<map>
using namespace std;
//�洢������id�Ľṹ��
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
			//Ѱ��ƥ���id,��ƥ�䵽�����������ֱ����match��,ע���һ��ֵ��ҪΪ����id����majia
			for (int i = 0; i < n; i++) {
				for (int j = i+1; j < n; j++) {
					if (ni[i].id == ni[j].id) {
						match.insert(make_pair(ni[i].name, ni[j].name));
						                     //  ����id        majia
						break;
					}
				}
			}
			for (iter = match.begin(); iter != match.end(); iter++) {
				cout << (*iter).second << " is the MaJia of " << (*iter).first << endl;
			}
			//��ĿҪ��ÿ��case���һ��\n
			cout << endl;
		}
	}
	return 0;
}
