#include<iostream>
#include<cstdio>
#include<vector>
#include<cmath>
using namespace std;

/*
 * 题目大意:给定 Mersenne number定义2^p-1(p为素数)
 *       给定k(k<=63),求所有小于k的p使得2^p-1为合数
 *
 * 解题思路:质因数分解,但是这里计算p=61则会超时.
 *       已知2^61-1为素数(梅森素数),将61从prime[]中去除
 */
int prime[] = {11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61};

int main() {
	int k;
	scanf("%d", &k);
	for (int i = 0; prime[i] <= k; i++) {
		vector<long long>factors;
		long long num = (long long)pow(2.0, prime[i])-1;
		bool Composite = false;
		long long temp = num;
		for (long long i = 2; i * i <= temp; i++) {
			if (temp % i == 0) {
				temp = temp/i;
				Composite = true;
				factors.push_back(i);
			}
		}
		factors.push_back(temp);
		if (Composite) {
			cout << factors[0];
			for (int i = 1; i < factors.size(); i++) {
				cout << " * " << factors[i];
			}
			cout << " = " << num << " = ( 2 ^ " << prime[i] << " ) - 1" << endl;
		}
	}
}

