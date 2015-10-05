/*
 * 1006 Team Rankings.cpp
 *
 *  Created on: 2015��9��29��
 *      Author: ABCD
 */
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
/*
 * ��Ŀ����:��ABCDE��5����ĸ���������Ϊһ��Ranking,����n������
 *       ������������ranking��distanceΪ ��ĸ��(AB,AC,AD,AE...)������ranking�е��Ⱥ�˳��ͬ������֮��
 *       ����ʾ���뿴��Ŀ
 * ����˼·:
 *       ���ڸ�����n��ranking,��'ABCDE'������'EDCBA'(ʹ��next_permutation����,ԭ���Լ���)
 *       �ֱ��n��ranking�е�ÿ��ranking����distance�����,����һ����Сֵmedian�Ͷ�Ӧ��median_ranking
 */

using namespace std;
string ranking[101];

//����dis�ķ�ʽ
int cal_dis(string s1, string s2) {
	int pos1[5][5], pos2[5][5];
	int dif = 0;
	//�洢��ĸ���ֵ��Ⱥ�˳���pos����,pos[n][m] (n:A=0,B=1,C=2,D=3,E=4; mͬ��)
	//pos[n][m] = 1 ��ʾ n��mǰ��(�±��С); pos[n][m] = -1 ��ʾ n��m����
	//����j=i+1��֤�˲�����Խ���(��n==m)�����;
	//����pos�����и�����:�����ڶԽ��߶ԳƵ�Ԫ�ػ�Ϊ�෴��,��pos[n][m] = -1*pos[m][n]
	for (int i = 0; i < s1.length(); i++) {
		for (int j = i+1; j < s1.length(); j++) {
			pos1[s1[i]-'A'][s1[j]-'A'] = (i < j) ? 1 : -1;
			pos2[s2[i]-'A'][s2[j]-'A'] = (i < j) ? 1 : -1;
			pos1[s1[j]-'A'][s1[i]-'A'] = -1*(pos1[s1[i]-'A'][s1[j]-'A']);
			pos2[s2[j]-'A'][s2[i]-'A'] = -1*(pos2[s2[i]-'A'][s2[j]-'A']);
		}
	}
	//����dis,���pos1[n][m] != pos2[n][m]���ʾ��������ranking��n��m���Ⱥ�˳��ͬ
	for (int i = 0; i < s1.length(); i++) {
		for (int j = 0; j < s1.length(); j++) {
			if (i == j) continue;
			if (pos1[i][j] != pos2[i][j]) dif++;
		}
	}
	//�����ظ�����,��Ҫ���������2(n=1,m=2��n=2,m=1�ȵ�)
	return dif/2;
}

int main() {
	int n;
	while (scanf("%d", &n) && n != 0) {
		for (int i = 0; i < n; i++) {
			cin >> ranking[i];
		}
		int sum, median = 9999;
		string median_ranking, s = "ABCDE";
		do {
			sum = 0;
			for (int i = 0; i < n; i++) {
				sum += cal_dis(ranking[i], s);
			}
			if (sum < median) {
				median = sum;
				median_ranking = s;
			}
		} while(next_permutation(s.begin(), s.end()));   //next_permutation()����,��������ȫ����
		cout << median_ranking << " is the median ranking with value " << median << "." << endl;
	}
}
