#include<iostream>
#include<cstdio>
#include<string>

/*
 * ��Ŀ����:3���ַ���A,B,C,����A��B�е���ĸ���������,ֻҪ���ı�������ԭ�ַ����е�˳��
 *     ��n������������,��A��B��ĸ���������ܷ�õ�C,�������yes,���������no
 *     ��������������֤C�ĳ��ȵ���A��B�ĳ���֮��
 * ����˼·:
 *     ���ǿ��Դ�C����,���Ҫ������Ŀ��Ҫ��,��ô����C�����⴦���ַ���Ȼƥ��A��B�е�һ��
 *     ����:C[0]��Ȼƥ��A[0]��B[0],Ȼ�����ǿ���ͬʱ����C��ƥ���ַ������±�,һ����������ƥ�������Ϳ���ֱ�ӷ���false
 *
 *     ������õ��Ǵ�C�����һλ��ʼ��ǰƥ��,�����ȽϷ���,��ƥ��λ�õ��±���ǵ�ǰδƥ��ĳ���
 */

using namespace std;

string s1, s2, s3;
bool flag;

void dfs(int l1, int l2, int l3) {
	//l3Ϊ0��ʾ�Ѿ�ƥ���������һ���ַ�
	if (l3 == 0) {
		flag = true;
		return;
	}
	//ֻ�����ֿ���,������ֶ���ƥ��ֱ�ӷ���
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
		//�ݹ鷽��ʵ��ƥ��,Ҳ�����÷ǵݹ�ʵ��,���ȶ���Ҫ��1
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

