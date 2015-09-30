#include<iostream>
#include<string>
#include<cstdio>
using namespace std;

/*
 * 题目大意是:用数字1~26代表英文字母A~Z，现在给出一串标准的数字串,对应翻译成字母串有多少种翻译方式
 *
 * 解法:动态规划
 * 一、 当只有1个数字时,初始状态f1 = 1, f2 = 1(f1代表上两步状态,f2代表上一步状态,刚开始都是同一状态),decodingNum表示翻译出来的总数;
 * 二、当大于1个数字时,分3种情况讨论:
 *     code[i] == '0':
 *     1、此时'0'只有跟前一位组成一个整体才能满足题意,所以对应的翻译方式数量跟上两步状态相同,所以decodingNum = f1;
 *     code[i] != '0':
 *     2、code[i-1]与code[i]组成的数字在区间(10,26]之间(不等于20)
 *       此时既可以把code[i]单独拿出来作为一个字母(decodingNum=f2) + code[i]与code[i-1]合起来表示一个字母(decodingNum=f1)
 *       所以decodingNum = f1 + f2
 *     3、code[i-1]与code[i]组成的数字不能表示一个字母,此时只能把code[i]单独拿出来作为一个字母,所以decodingNum=f2
 *
 *     f1 = f2, f2 = decodingNum;     //准备判断下一状态,上一步状态变成上两步状态.当前状态变成上一步状态
 *     i++,返回二
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
