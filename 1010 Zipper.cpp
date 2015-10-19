#include<iostream>
#include<cstdio>
#include<string>

/*
 * 题目大意:3个字符串A,B,C,其中A与B中的字母可以随便混合,只要不改变它们在原字符串中的顺序
 *     有n组这样的样例,问A与B字母的随机混合能否得到C,能则输出yes,不能则输出no
 *     其中输入样例保证C的长度等于A与B的长度之和
 * 解题思路:
 *     我们可以从C考虑,如果要满足题目的要求,那么对于C的任意处的字符必然匹配A或B中的一个
 *     例如:C[0]必然匹配A[0]或B[0],然后我们可以同时递增C和匹配字符串的下标,一旦碰到都不匹配的情况就可以直接返回false
 *
 *     这里采用的是从C的最后一位开始向前匹配,这样比较方便,带匹配位置的下标就是当前未匹配的长度
 */

using namespace std;

string s1, s2, s3;
bool flag;

void dfs(int l1, int l2, int l3) {
	//l3为0表示已经匹配完了最后一个字符
	if (l3 == 0) {
		flag = true;
		return;
	}
	//只有两种可能,如果两种都不匹配直接返回
	if (!flag && l1 >= 0 && s1[l1] == s3[l3])
		dfs(l1-1, l2, l3-1);
	if (!flag && l2 >= 0 && s2[l2] == s3[l3])
		dfs(l1, l2-1, l3-1);
	return;
}


int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int n, time = 0;
	scanf("%d", &n);
	while (n--) {
		time++;
		flag = false;
		cin >> s1 >> s2 >> s3;
		//递归方法实现匹配,也可以用非递归实现,长度都需要减1
		dfs(s1.length()-1, s2.length()-1, s3.length()-1);
		if (flag) {
			printf("Data set %d: yes\n", time);
		} else {
			printf("Date set %d: no\n", time);
		}
	}
	//fclose(stdin);
	//fclose(stdout);
	return 0;
}

