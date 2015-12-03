#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;

#define MAX 10001
int prime[MAX];
int num_prime = 0;
bool isPrime[MAX];

//线性筛法
void Prime() {
	for (int i = 2; i < MAX; i++) {
		if (isPrime[i]) {
			prime[num_prime++] = i;
		}
		for (int j = 0; j < num_prime && i*prime[j] < MAX; j++) {
			isPrime[prime[j]*i] = false;
			/*
			 * key point:
			 * if i % prime[j] == 0 , then prime[j]*k = i
			 * for j' > j, we need not consider prime[j']*i
			 * because prime[j']*i = prime[j']*prime[j]*k
			 * so prime[j]*(prime[j']*k)
			 * this means that we can find an i to replace (prime[j']*k) after some loops
			 * so we can break this loop.
			 */
			if (i % prime[j] == 0) break;
		}
	}
}

//检查连续素数和是否等于n,由于范围只到10000,所以暴力即可
int cal(int n) {
	int num = 0, sum;
	for (int i = 0; i < num_prime; i++) {
		sum = 0;
		for (int j = i; sum < n && j < num_prime; j++) {
			sum += prime[j];
			if (sum == n)
				num++;
		}
	}
	return num;
}

int main() {
	int n;
	memset(isPrime, true, sizeof(isPrime));
	Prime();
	while (cin >> n && n != 0) {
		printf("%d\n", cal(n));
	}
}
