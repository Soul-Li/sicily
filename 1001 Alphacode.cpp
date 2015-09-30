#include<iostream>
#include<string>
#include<cstdio>
using namespace std;

/*
 * ��Ŀ������:������1~26����Ӣ����ĸA~Z�����ڸ���һ����׼�����ִ�,��Ӧ�������ĸ���ж����ַ��뷽ʽ
 *
 * �ⷨ:��̬�滮
 * һ�� ��ֻ��1������ʱ,��ʼ״̬f1 = 1, f2 = 1(f1����������״̬,f2������һ��״̬,�տ�ʼ����ͬһ״̬),decodingNum��ʾ�������������;
 * ����������1������ʱ,��3���������:
 *     code[i] == '0':
 *     1����ʱ'0'ֻ�и�ǰһλ���һ�����������������,���Զ�Ӧ�ķ��뷽ʽ������������״̬��ͬ,����decodingNum = f1;
 *     code[i] != '0':
 *     2��code[i-1]��code[i]��ɵ�����������(10,26]֮��(������20)
 *       ��ʱ�ȿ��԰�code[i]�����ó�����Ϊһ����ĸ(decodingNum=f2) + code[i]��code[i-1]��������ʾһ����ĸ(decodingNum=f1)
 *       ����decodingNum = f1 + f2
 *     3��code[i-1]��code[i]��ɵ����ֲ��ܱ�ʾһ����ĸ,��ʱֻ�ܰ�code[i]�����ó�����Ϊһ����ĸ,����decodingNum=f2
 *
 *     f1 = f2, f2 = decodingNum;     //׼���ж���һ״̬,��һ��״̬���������״̬.��ǰ״̬�����һ��״̬
 *     i++,���ض�
 */

int main() {
	string code;
	while (1) {
		cin >> code;
		if (code == "0") break;
		int f1, f2, decodingNum;
		f1 = f2 = 1;
		decodingNum = f1;
		for (int i = 1; i < code.length(); i++) {
			if (code[i] == '0') {
				decodingNum = f1;
			} else {
				int num = (code[i-1]-'0')*10+(code[i]-'0');
				if (num > 10 && num <= 26)
					decodingNum = f1+f2;
				else
					decodingNum = f2;
			}
			f1 = f2;
			f2 = decodingNum;
		}
		cout << decodingNum << endl;
	}
}
