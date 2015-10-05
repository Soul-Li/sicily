#include<iostream>
#include<cstdio>
#include<vector>
#include<cmath>
using namespace std;

/*
 * ��Ŀ����:���� Mersenne number����2^p-1(pΪ����)
 *       ����k(k<=63),������С��k��pʹ��2^p-1Ϊ����
 *
 * ����˼·:�������ֽ�,�����������p=61��ᳬʱ.
 *       ��֪2^61-1Ϊ����(÷ɭ����),��61��prime[]��ȥ��
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

