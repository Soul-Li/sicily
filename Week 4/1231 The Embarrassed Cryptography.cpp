#include<iostream>
#include<cstdlib>
#include<cstdio>
using namespace std;
//10^6,之前一直写成100000导致WA...
#define MAX 1000001
int prime[MAX];
int num_prime = 0;
int isPrime[MAX];

//线性筛法
void Prime() {
	for (int i = 2; i < MAX; i++) {
		if (isPrime[i]) {
			prime[num_prime++] = i;
		}
		for (int j = 0; j < num_prime && i*prime[j] < MAX; j++) {
			isPrime[prime[j]*i] = 0;
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

int main() {
	string K;
	int L;
	for (int i = 0; i < MAX; i++) {
		prime[i] = 0;
		isPrime[i] = 1;
	}
	Prime();
	while (1) {
		cin >> K >> L;
		if (K == "0" && L == 0) break;

		int i, j;
		bool flag = true;

		for (i = 2; i < L; i++) {
			if (isPrime[i]) {
				long mod = 0;

				//高精度取余
				for (j = 0; K[j] != '\0'; j++) {
					mod = (mod*10+(K[j]-'0')) % i;
				}
				//余数为0
				if (mod == 0) {
					flag = false;
					break;
				}
			}
		}
		if (flag) printf("GOOD\n");
		else printf("BAD %d\n", i);
	}
	return 0;
}
