#include<iostream>
#include<string>
#include<map>
#include<algorithm>
using namespace std;

/*
 * ����,ע��friend list ��Сд������,�˴��п�����sender list��ΪСд�ڿ�
 * �����ڲ���mapǰ��Ҫȫ��ת��ΪСд���д
 * ʣ�µľ��Ǽ򵥵Ĳ���
 * Ϊ�����ظ�����,����map�ĵڶ�������Ϊint��ʾ���ҵ��Ĵ���
 * ֻ�е��ҵ�name�Ҵ���Ϊ0ʱ����һ�β鵽count++
 * �������������ȥcount���ý��
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
			//iter����Ϊend,��Ϊ��Щsender�ǲ���friend list�е�
			if (iter != friends.end() && (*iter).second == 0) {
				count++;
				//������ҵ��ظ�����
				(*iter).second++;
			}
		}
		cout << n-count << endl;
		//ϸ������
		friends.clear();
	}
}
