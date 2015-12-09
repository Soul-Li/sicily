#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

/*
 * 实际就是求不大于k的最大素数和不小于k的最小素数之差
 */

#define MAX 1300000

int prime_num = 0;
int prime[MAX];
bool isPrime[MAX];

void Prime() {
    memset(isPrime, true, sizeof(isPrime));
    for (int i = 2; i < MAX; i++) {
        if (isPrime[i])
            prime[prime_num++] = i;
        for (int j = 0; j < prime_num && i*prime[j] < MAX; j++) {
            isPrime[i*prime[j]] = false;
            if (i % prime[j] == 0) break;
        }
    }
}

int main() {
    int num;
    Prime();
    while (cin >> num && num != 0) {
        int i, j;
        for (i = num; !isPrime[i]; i--);
        for (j = num; !isPrime[j]; j++);
        printf("%d\n", j-i);
    }
}
