#include <cstdio>
#include <cmath>
#include <cstring>

using namespace std;

//���ٳ˷���û�㶮
long long mul(long long a, long long b, long long mod) {
    long long c = 0;
    const int base = 2;
    for (; b != 0; b /= base) {
        c += (b % base) * a;
        c %= mod;
        a = (a * base) % mod;
    }
    return c;
}

long long cube(long long x, long long mod){
    return mul(mul(x,x,mod), x, mod);
}

int main () {
    int t, length;
    // result ������¼���ս��
    // remain ������ǰ����Ҫ�Ƚϵ�β��
    long long result, remain, power, step;
    char str[11];

    scanf("%d",&t);
    while( t-- ){
        scanf("%s",&str);
        length = strlen(str);
        result = remain = str[length-1] - '0';
        power = 10;

        // ֻ��Ҫ��������Ƚ�β����ǰһλβ������˾ͱȽ���һλ
        // һ��ʼ��1^3β��Ϊ1,3^3β��Ϊ7,7^3β��Ϊ3,9^3β��Ϊ9
        if( result == 3 ) result = 7;
        else if( result == 7 ) result = 3;

        for( int i = length - 2; i >= 0; --i ){
            remain += (str[i] - '0') * power;
            step = power;
            power *= 10;
            // �����ǰ�����ϣ���ô�ڵ�ǰλ�����ټ�1������result����һ��step
            while( cube(result,power) != remain ){
                result += step;
            }
        }
        printf("%lld\n",result);
    }

    return 0;
}
