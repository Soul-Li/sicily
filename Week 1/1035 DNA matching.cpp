#include<iostream>
#include<string>
#include<vector>
using namespace std;

//DNA匹配
bool match(const string& s1, const string& s2) {
	if (s1.length() != s2.length()) return false;
	for (int i = 0; i < s1.length(); i++) {
		switch(s1[i]) {
		case 'A':
			if (s2[i] != 'T') return false;
			break;
		case 'G':
			if (s2[i] != 'C') return false;
			break;
		case 'C':
			if (s2[i] != 'G') return false;
			break;
		case 'T':
			if (s2[i] != 'A') return false;
			break;
		default:
			break;
		}
	}
	return true;
}

int main() {
	int T, n, count = 0;
	string s;
	vector<string> DNA;
	vector<string>::iterator iter1, iter2;
	cin >> T;
	while (T--) {
		cin >> n;
		count = 0;
		for (int i = 0; i < n; i++) {
			cin >> s;
			DNA.push_back(s);
		}
		//因为每次匹配都会移除第一个DNA串,所以iter1=DNA.begin()比较合理
		for (iter1 = DNA.begin(); iter1 != DNA.end(); iter1=DNA.begin()) {
			//使用iter+1而不是iter++,基于iterator的特性
			for (iter2 = iter1+1; iter2 != DNA.end(); iter2++) {
				if (match((*iter1), (*iter2))) {
					count++;
					DNA.erase(iter2);
					break;
				}
			}
			//匹没匹配到都删除掉需匹配的DNA串
			DNA.erase(iter1);
		}
		cout << count << endl;
		DNA.clear();
	}
	return 0;
}
